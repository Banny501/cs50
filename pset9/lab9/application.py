import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if name == "" or not name.isalnum():
            return render_template("err.html", msg="Wrong name!")
        elif not check_date(month, day):
            return render_template("err.html", msg="Wrong date!")
        else:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            return redirect("/")

    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route("/err")
def err():
    return render_template("err.html", msg="")



def check_date(month, day):
    MONTH={
    1:  31,
    2:  28,
    3:  31,
    4:  30,
    5:  31,
    6:  30,
    7:  31,
    8:  31,
    9:  30,
    10: 31,
    11: 30,
    12: 31
    }

    if month == "" or day == "":
        return False
    elif MONTH[int(month)] < int(day) and int(day) > 0:
        return False
    else:
        return True
