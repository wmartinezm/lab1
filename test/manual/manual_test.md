The following is the initial test to verify that Lab1 is working.

Project Setup:
1. Open the project on VS Code.
2. Make sure your Discoveri board is connecte to yourpc/laptop.
3. Go trough the code and make sure that you understand the overall expected behavior of the system.

Upload the board's firmware:
1. Make sure the peoject compiles by runing the command: pio run
2. Flash the Discovery board with the command: pio run --target upload

Expected behavior:
The Red LED (LED0) should blink every ~500 ms.
The Orange LED (LED1) should blink every ~1 s.

Note: If this is not the behavior you are seeing check the parts pf the code that are handlink the LEDs to trace the root od the issue.

