# eb6
Firmware and Test-Tools for the El Burrito EB6 6cm FM/CW transceiver 

This V0 branch uses the first version of the pin connections, which
are now obsolete. For Testing you can use V0 anyway, the minimal
connections are given in the code are valid. 

All connections have changed in the main branch, this is just to keep
the first version saved

. 
ESP32 pin (old)	goes to	 description	
			
13	 CE  	 output, enables MAX2870	
17	 rxa 	 output to EB6, enables TX 	
14	 txa 	 output to EB6, enables RX	
27	 FM  	 output, enab. FM modulation, +3.3V FM	
26	 (1) 	 future use	
35	 det 	 input, from EB6, TX power detector 	
34	 MUX 	 input, MAX2870 MUX	
39	 sel 	 Push Button "select" on the QEI (*)	
38	 QA  	 input, QEI A 	 frequency up (*)
37	 QB  	 input, QEI B 	 frequency down (*)
36	 ptt 	 input, Push to talk (*)	
2	 (2) 	 future use	
17	 (3) 	 future use	
5	 LE  	 output, Latch data to MAX2870	
18	 CLK 	 output, SPI Clock to MAX2870	
23	 data	 output, SPI MOSI to MAX2870	
19	 sdi 	 not used, but belongs to SPI definition	
22	 RD  	 RS232 Txd out to EB6 DRA818u RD 	
21	 TX  	 RS232 Rxd in from EB6 DRA818u TD 	


