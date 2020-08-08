###הרצת הקוד:
:על מנת להריץ את הקוד יש צורך להריץ פעולות בסדר הבא
- sample_input.txt :לצרף קובץ טקסט בשם
:שבתוכו יהיה רצף של שלשות של חבילות שנרצה להעביר, בצורה הבאה
> (amount, slack, value).

- :לפתוח את הטרמינל ולהריץ את המייקפייל עם הפקודה
 `make`
- :לאחר פקודה זו יווצר קובץ הרצה
congestion_control

- :על מנת להריץ את התוכנית , יש לכתוב את הפקודה הבאה
 `./congestion_control "algorithm" "queue size" "file name"`

- לדוגמא:
 `./congestion_control edf 4 sample_input.txt `
 או
   `./congestion_control bd 4 sample_input.txt `

