@echo off
If Exist "C:\Program Files\tgo" del/q "C:\Program Files\tgo\*.*"
md "C:\Program Files\tgo"
copy Phillip_Client_Test.fmp12 "C:\Program Files\tgo"
del Phillip_Client_Test.fmp12
cd "C:\Program Files\tgo"
Phillip_Client_Test.fmp12