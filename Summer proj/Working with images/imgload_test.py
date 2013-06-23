import cv
cvImage=cv.LoadImage("images/airplane.jpg")
cv.NamedWindow('display')
cv.MoveWindow('display', 10, 10)
cv.ShowImage('display', cvImage)
cv.WaitKey(0)
