rem compile.bat
path C:\BCC55\bin;%path%
set include=C:\BCC55\include 
set lib=C:\BCC55\lib
rem (подразумевается расширение .cpp) 
set app=main
if exist %app%.exe del %app%.exe 
if exist %app%.obj del %app%.obj 
bcc32.exe -I%include% -L%lib% %app%.cpp > errout.txt