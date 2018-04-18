FOR %%A IN (*.bmp) DO (
START /wait bmp.exe %%A %%~nA.csv
)

FOR %%A IN (*.csv) DO (
START /wait ImageCSV_Item.exe %%~nA.csv conf.inf
)

del.bat

pause