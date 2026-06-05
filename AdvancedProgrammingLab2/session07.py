from turtle import Turtle, Screen

tim = Turtle()
screen = Screen()
screen.listen()

def move_right():
    tim.setheading(0)
    tim.forward(100)

def move_up():
    tim.setheading(90)
    tim.forward(100)

def move_left():
    tim.setheading(180)
    tim.forward(100)

def move_down():
    tim.setheading(270)
    tim.forward(100)

screen.onkey(move_right, "Right")
screen.onkey(move_up, "Up")
screen.onkey(move_left, "Left")
screen.onkey(move_down, "Down")



tim.shape("turtle")
tim.shapesize(stretch_wid=2, stretch_len=2)
tim.color("green")
tim.speed(1)
tim.pensize(5)

screen.exitonclick()