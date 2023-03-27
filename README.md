# eb6
Firmware and Test-Tools for the El Burrito EB6 6cm FM/CW transceiver 

This are the new order of connections  with the "Mezzanine-PCB", which
connects the ESP32 and the MAX2870 together, saveing lot of work with the 
connections and make the El burrito look much better

with 			
ESP32 pin	goes to	 description	
"mezzanine"	

26	 CE  	 output, enables MAX2870

17	 rxa 	 output to EB6, enables TX 

13	 txa 	 output to EB6, enables RX

21	 FM  	 output, enab. FM modulation, +3.3V FM	

23	 (1) 	 future use

2	 det 	 input, from EB6, TX power detector 

35	 MUX 	 input, MAX2870 MUX	

37	 sel 	 Push Button "select" on the QEI (*)

39	 QA  	 input, QEI A 	 frequency up (*)

38	 QB  	 input, QEI B 	 frequency down (*)

36	 ptt 	 input, Push to talk (*)

19	 (2) 	 future use

22	 (3) 	 future use

27	 LE  	 output, Latch data to MAX2870	

14	 CLK 	 output, SPI Clock to MAX2870	

12	 data	 output, SPI MOSI to MAX2870

18	 sdi 	 not used, but belongs to SPI definition

5	 RD  	 RS232 Txd out to EB6 DRA818u RD 

34	 TX  	 RS232 Rxd in from EB6 DRA818u TD 	
			
"(*) the 2 capacitors at 36/37 and 38/39 on the ESP32
board must be removed."			
