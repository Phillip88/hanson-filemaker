@ECHO OFF
set bananaDate=11-20-2012

set currentDate=%date%
set mmddyyyy=%currentDate:~4,10%
set mmddyyyy=%mmddyyyy:/=-%

date %bananaDate%
echo "The system date has been changed to Nov 20, 2012."

SET /P anykey=Press any key to restore date!:

date %mmddyyyy%



