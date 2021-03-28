import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        # Get forms
        buy_simbol = request.form.get("symbol")
        buy_shares = request.form.get("shares")

        # Check forms
        if not buy_simbol:
            return apology("Missing Symbol", 400)
        elif not buy_shares:
            return apology("Missing Shares", 400)
        elif not buy_shares.isdigit():
            return apology("wrong shares", 400)

        comp_quote = lookup(buy_simbol)
        if not lookup(buy_simbol):
            return apology("invalid symbol", 400)

        usr_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
        app.logger.debug("usr_cash : %d", usr_cash)

        app.logger.debug("comp_quote : ")
        app.logger.debug(comp_quote)

        if usr_cash < (int(buy_shares) * comp_quote["price"]):
            return apology("can't afford", 400)

        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "POST":
        return apology("TODO")
    else:
        return render_template("history.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        return apology("TODO")
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Get forms
        reg_username = request.form.get("username")
        reg_pass = request.form.get("password")
        reg_pass_confirmation = request.form.get("confirmation")
        # Ensure that all was submitted
        if not reg_username:
            return apology("must provide username", 403)
        elif not reg_pass:
            return apology("must provide password", 403)
        elif not reg_pass_confirmation:
            return apology("must provide password twice", 403)
        elif reg_pass != reg_pass_confirmation:
            return apology("password and password confirmation must be the same", 403)
        elif  len(db.execute("SELECT * FROM users WHERE username = ?", reg_username)) > 0:
            return apology("username is already taken", 403)

        # Write to database
        db.execute("INSERT INTO users (username ,hash) VALUES (?, ?)", reg_username, generate_password_hash(reg_pass))

        # Login in
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = ?", reg_username)
        flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        return apology("TODO")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
