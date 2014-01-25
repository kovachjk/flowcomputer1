

//**************************************************************
//********* FTP CLIENT *****************************************
//**************************************************************
#if defined(STACK_USE_FTP_CLIENT)
BOOL FTPClient(void)
{
    BYTE v;
	static BYTE i;
	static BOOL DataReceivedOK;
	    TICK currentTick;
	BYTE myData[50];
	
	switch(smFTPC)
	{
		case SM_FTPC_WAIT:
			if(!FTPCFlags.Bits.bInputData)
			ReadSerialData();
			else
			{
			lastActivity = TickGet();
			smFTPC = smFTPCnext;
			FTPCFlags.Bits.bInputData = FALSE;
			}
			currentTick = TickGet();
			       currentTick = TickGetDiff(currentTick, lastActivity);
			         if ( currentTick >= FTPC_TIMEOUT ) // if timeout close the socket
			         {
			Confirm = 0;
			             lastActivity = TickGet();
			         TCPFlush(FTPCDataSocket);
			TCPDisconnect(FTPCDataSocket);
			smFTPC = SM_FTPC_GETLINE;
			smFTPCnext = SM_FTPC_QUIT;
		}
		break;
		
		case SM_FTPC_GET_HOST:
			lastActivity    = TickGet();
			putrsUART("00 - FTP Client 1.0 Start Process\r\n");
			putrsUART2("00 - FTP Client 1.0 Start Process\r\n");
			     FTPStringLen    = 0;
			     FTPCFlags.Val   = 0;
			/*
			putrsUART2("01 - Host IP Address\r\n");
			smFTPC = SM_FTPC_WAIT;
			smFTPCnext = SM_FTPC_GET_PORT;
			*/
			smFTPC = SM_FTPC_GET_FILENAME;
		break;
		
		case SM_FTPC_GET_PORT:
			strcpy(ftp.HostName,FTPString);
			putrsUART2("02 - Local Port\r\n");
			smFTPC = SM_FTPC_WAIT;
			smFTPCnext = SM_FTPC_GET_USER;
		break;
		
		case SM_FTPC_GET_USER:
			ftp.FTPCDataPort.Val = atoi(FTPString);
			putrsUART2("03 - Username\r\n");
			smFTPC = SM_FTPC_WAIT;
			smFTPCnext = SM_FTPC_GET_PASS;
		break;
		
		case SM_FTPC_GET_PASS:
			strcpy(ftp.username,FTPString);
			putrsUART2("04 - Password\r\n");
			smFTPC = SM_FTPC_WAIT;
			smFTPCnext = SM_FTPC_GET_FILENAME;
		break;
		
		case SM_FTPC_GET_FILENAME:
			//strcpy(ftp.password,FTPString);
			putrsUART("05 - File Name\r\n");
			putrsUART2("05 - File Name\r\n");
			smFTPC = SM_FTPC_WAIT;
			smFTPCnext = SM_FTPC_INIT;
		break;
		
		case SM_FTPC_INIT:
			lastActivity    = TickGet();
			strcpy(ftp.filename,FTPString);
			Confirm = 1;
			DataReceivedOK = FALSE;
			
			StringToIPAddress(ftp.HostName, &IP_Server);
			//FTPCSocket     = TCPOpen((DWORD)&ftp.HostName, TCP_OPEN_RAM_HOST, FTP_COMMAND_PORT, TCP_PURPOSE_FTP_COMMAND);
			FTPCSocket     = TCPOpen(IP_Server.Val, TCP_OPEN_IP_ADDRESS, FTP_COMMAND_PORT, TCP_PURPOSE_FTP_COMMAND);
			
			//if(FTPCDataSocket == INVALID_SOCKET)
			// FTPCDataSocket = TCPOpen(0, TCP_OPEN_SERVER, ftp.FTPCDataPort.Val, TCP_PURPOSE_FTP_DATA);
			if(FTPCSocket == INVALID_SOCKET)
			     goto _ftp_client_bail;
			smFTPC          = SM_FTPC_CONNECTWAIT;
			FTPStringLen    = 0;
		break;
		
		case SM_FTPC_CONNECTWAIT: //  attesa di connessione
			if (TCPIsConnected(FTPCSocket))
			{
				smFTPC   = SM_FTPC_GETLINE;
				smFTPCnext = SM_FTPC_USERNAME;
			}
			currentTick = TickGet();
			currentTick = TickGetDiff(currentTick, lastActivity);
			if ( currentTick >= FTPC_TIMEOUT) // if timeout close the socket
			{
				putrsUART("Invalid FTP Socket: ");
				itoa(FTPCSocket, FTPString);
				putsUART(FTPString);
				putrsUART("\r\n");
				goto _ftp_client_bail;
			}
		break;
		
		case SM_FTPC_GETLINE:
		ReadLine();
		if(FTPCFlags.Bits.bReadLine)
		{
			lastActivity    = TickGet();
			FTPCFlags.Bits.bReadLine = FALSE;
			smFTPC = smFTPCnext;
		}	
		currentTick = TickGet();
		currentTick = TickGetDiff(currentTick, lastActivity);
		if ( currentTick >= FTPC_TIMEOUT ) // if timeout close the socket
		{
			TCPFlush(FTPCSocket);
			TCPDisconnect(FTPCSocket);
			smFTPC = SM_FTPC_BAIL;
			putrsUART("No Response from FTP Server: ");
			itoa(FTPCDataSocket, FTPString);
			putsUART(FTPString);
			putrsUART("\r\n");
		}
		break;
		
		case SM_FTPC_USERNAME:
			// Could get a 120 (service available in the future) but treat as error.
			if (FTPCReq != 220)	goto _ftp_client_bail;
			smFTPCnext = SM_FTPC_PASSWORD;
			SendFTPCMessage();
			lastActivity    = TickGet();
		break;
		
		case SM_FTPC_PASSWORD: // send password if necessary
			if (FTPCReq == 230)
			{
				// That's nice, don't need password
				smFTPC = SM_FTPC_SETMODE;
				break;
			}
			if (FTPCReq != 331)goto _ftp_client_bail;
			// Go directly to jail.  Do not pass GO.  Do not collect $200...
			smFTPCnext = SM_FTPC_SETMODE;
			SendFTPCMessage();
			lastActivity    = TickGet();
		break;
		
		case SM_FTPC_SETMODE:
			if (FTPCReq != 230)goto _ftp_client_bail;
			//smFTPCnext = SM_FTPC_SETDIR;
			smFTPCnext = SM_FTPC_SETPORT;
			SendFTPCMessage();
			lastActivity    = TickGet();
		break;
		
		case SM_FTPC_SETDIR:
			if (FTPCReq != 200)	goto _ftp_client_bail;
			if (!ftp.dir[0])smFTPC = SM_FTPC_SETPORT;
			else
			{
				smFTPCnext = SM_FTPC_SETPORT;
				SendFTPCMessage();
				lastActivity    = TickGet();
			}
		break;
		
		case SM_FTPC_SETPORT:
			smFTPCnext = SM_FTPC_CMD;
			SendFTPCMessage();
			lastActivity    = TickGet();
			FTPStringLen = 0;
		break;
		
		case SM_FTPC_CMD:
			if (FTPCReq != 200)goto _ftp_client_bail;
			smFTPCnext = SM_FTPC_UPLOAD;
			SendFTPCMessage();
			lastActivity    = TickGet();
			FTPCDataSocketOK = FALSE;
			if(FTPCDataSocket == INVALID_SOCKET)
			FTPCDataSocket = TCPOpen(0, TCP_OPEN_SERVER, ftp.FTPCDataPort.Val, TCP_PURPOSE_FTP_DATA);
		break;
		
		case SM_FTPC_UPLOAD:
			if (FTPCReq != 150 && FTPCReq != 125) goto _ftp_client_bail;// controllo messaggio inizio dati	
			if (!TCPIsConnected(FTPCDataSocket)) // controllo connessione FTP dati
			{
				currentTick = TickGet();
			    currentTick = TickGetDiff(currentTick, lastActivity);
			    if ( currentTick >= FTPC_TIMEOUT ) // if timeout close the socket
				{
					putrsUART("Invalid FTP Data Socket: ");
					itoa(FTPCDataSocket, FTPString);
					putsUART(FTPString);
					putrsUART("\r\n");
					goto _ftp_client_bail;
				}
				break;
			}
			else if(!FTPCDataSocketOK)
			{
				FTPCDataSocketOK = TRUE;
				count2 = 0;
				EnableDec2 = 0;
				for(i=0; i<45; i++)
				BuffString='\0';
				putrsUART("10 - Init Complete\r\n");
				putrsUART2("10 - Init Complete\r\n");
			}
			else if (EnableDec2)
			{
				lastActivity    = TickGet();
				EnableDec2 = 0;
				i = 0;
				DataReceivedOK = TRUE;
				strcpy(myData, BuffString);
				while(myData)
				{
					// Make sure there is enough TCP TX FIFO space to put our response
				    if(TCPIsPutReady(FTPCDataSocket)<strlen(myData))TCPFlush(FTPCDataSocket);
					else
					{
						TCPPut(FTPCDataSocket,myData[i++]);
					}
				}
				TCPFlush(FTPCDataSocket);
				putcUART('#');
				LED3_IO = 0;
			}
		
			currentTick = TickGet();
			currentTick = TickGetDiff(currentTick, lastActivity);
			if ( currentTick >= FTPC_TIMEOUT_DATA ) // if timeout close the socket
			{
				//if(myData[i-1]=='\r') TCPPutROMString(FTPCDataSocket,"\n");
				TCPPutROMString(FTPCDataSocket,"\n");
				TCPFlush(FTPCDataSocket);
				putrsUART("\r\n");
				Confirm = 0;
				EnableDec2 = 0;
				             lastActivity = TickGet();
				TCPDisconnect(FTPCDataSocket);
				smFTPC = SM_FTPC_GETLINE;
				smFTPCnext = SM_FTPC_QUIT;
			}
		break;
		
		case SM_FTPC_QUIT:
			if (FTPCReq != 226 )
			goto _ftp_client_bail;
			smFTPCnext = SM_FTPC_DONE;
			SendFTPCMessage();
		break;
			
			_ftp_client_bail:
			smFTPC = SM_FTPC_BAIL;
			// fall thru
			case SM_FTPC_BAIL:
			TCPDisconnect(FTPCSocket);
			if(!TCPIsConnected(FTPCSocket))
			{
			if(FTPCDataSocket != INVALID_SOCKET)
			{
			TCPDisconnect(FTPCDataSocket);
			//FTPCDataSocket = INVALID_SOCKET;
			}
			EnableFTPc = FALSE;
			smFTPC = SM_FTPC_GET_HOST;
			putrsUART("99 - FTP Error. Connection Closed.\r\n");
			putrsUART2("99 - FTP Error. Connection Closed.\r\n");
			return TRUE;
			}
		break;
	
		case SM_FTPC_DONE:
			TCPDisconnect(FTPCSocket);
			if(!TCPIsConnected(FTPCSocket))
			{
				if(FTPCDataSocket != INVALID_SOCKET)
				{
					TCPDisconnect(FTPCDataSocket);
					//FTPCDataSocket = INVALID_SOCKET;
				}
				EnableFTPc = FALSE;
				smFTPC = SM_FTPC_GET_HOST;
				if(DataReceivedOK == TRUE)
				{
					putrsUART("20 - FTP Complete Successfully\r\n");
					putrsUART2("20 - FTP Complete Successfully\r\n");
				}
				else
				{
					putrsUART("99 - FTP Error. Connection Closed.\r\n");
					putrsUART2("99 - FTP Error. Connection Closed.\r\n");
				}
				return TRUE;
			}
		break;
	}
	return TRUE;
} 
#endif