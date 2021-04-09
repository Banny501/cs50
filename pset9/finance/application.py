import os
import datetime

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
    index_balance = db.execute("SELECT * FROM balance WHERE user_id = ?", session["user_id"])
    summ_shares = 0
    for line in index_balance:
        index_share_list = lookup(line["symbol"])
        if not index_share_list:
            return apology("Not find symbol", line["symbol"])
        summ_shares += float(index_share_list["price"])
        line["price"] = usd(index_share_list["price"])
        line["total"] = usd(index_share_list["price"] * line["shares"])
    index_usr_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]

    return render_template("index.html", balance = index_balance, \
                                         cash = usd(index_usr_cash),\
                                         total_cash = usd(summ_shares + index_usr_cash) )


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
        elif int(buy_shares) <= 0:
            return apology("wrong shares", 400)

        comp_quote = lookup(buy_simbol)
        if not comp_quote:
            return apology("invalid symbol", 400)

        buy_usr_cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]

        if buy_usr_cash < (int(buy_shares) * comp_quote["price"]):
            return apology("can't afford", 400)
        else:
            old_balance = db.execute("SELECT * FROM balance WHERE symbol = ? AND name = ? AND user_id = ?",\
                                            comp_quote["symbol"], \
                                            comp_quote["name"], \
                                            session["user_id"])
            if not old_balance:
                db.execute("INSERT INTO balance (user_id, name, symbol, shares) \
                                VALUES (?, ?, ?, ?)", \
                                session["user_id"], \
                                comp_quote["name"], \
                                comp_quote["symbol"], \
                                int(buy_shares) )
            else:
                db.execute("UPDATE balance SET shares = ? WHERE name=? AND symbol=? AND user_id=?",\
                                int(buy_shares) + old_balance[0]["shares"], \
                                comp_quote["name"], \
                                comp_quote["symbol"], \
                                session["user_id"] )

            db.execute("INSERT INTO history (user_id, name, symbol, shares, price, total, date) \
                            VALUES (?, ?, ?, ?, ?, ?, ?)", \
                            session["user_id"], \
                            comp_quote["name"], \
                            comp_quote["symbol"], \
                            int(buy_shares), \
                            comp_quote["price"], \
                            comp_quote["price"] * int(buy_shares), \
                            datetime.datetime.now() )

            buy_usr_cash -= (int(buy_shares) * comp_quote["price"])
            db.execute("UPDATE users SET cash=? WHERE id = ?", buy_usr_cash, session["user_id"])
            flash("Bought!")
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_id=? ORDER BY date DESC", session["user_id"])
    for line in history:
        line["price"] = usd(line["price"])
    return render_template("history.html", history=history)


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
        quote_shares = lookup(request.form.get("symbol"))
        if not quote_shares:
            return apology("Wrong simbol")
        else:
            quote_message = "A share of {} ({}) costs {}.".format(
                                    quote_shares["name"], \
                                    quote_shares["symbol"], \
                                    usd(quote_shares["price"]) )
            return render_template("quote.html", message = quote_message)
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
            return apology("must provide username", 400)
        elif not reg_pass:
            return apology("must provide password", 400)
        elif not reg_pass_confirmation:
            return apology("must provide password twice", 400)
        elif reg_pass != reg_pass_confirmation:
            return apology("password and password confirmation must be the same", 400)
        elif len(db.execute("SELECT * FROM users WHERE username = ?", reg_username)) > 0:
            return apology("username is already taken", 400)

        # Write to database
        db.execute("INSERT INTO users (username ,hash) VALUES (?, ?)", \
                        reg_username, generate_password_hash(reg_pass))

        # Login in
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = ?", reg_username)[0]["id"]
        flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    sell_symbols = db.execute("SELECT symbol FROM balance WHERE user_id=?", session["user_id"])
    if request.method == "POST":
        simb_sell = request.form.get("symbol")
        shar_sell = request.form.get("shares")

        if not simb_sell:
            return apology("Missing Symbol", 400)
        elif not shar_sell:
            return apology("Missing Shares", 400)
        elif not simb_sell.isalpha():
            return apology("Wrong Symbol", 400)
        elif int(shar_sell) <= 0:
            return apology("Wrong Shares", 400)
        usr_simb_list = []
        for item in sell_symbols:
            usr_simb_list.append(item["symbol"])
        if simb_sell not in usr_simb_list:
            return apology("simbol not found", simb_sell)

        sell_comp_quote = lookup(simb_sell)
        sell_usr_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        sell_usr_balance = db.execute("SELECT * FROM balance WHERE user_id = ?", session["user_id"])

        sell_balance_counter = 0
        for item in sell_usr_balance:
            if sell_comp_quote["name"] == item["name"] and sell_comp_quote["symbol"] == simb_sell:
                sell_balance_counter = int(item["shares"])

        if sell_balance_counter == 0:
            return apology("Not found", 400)
        elif sell_balance_counter < int(shar_sell):
            return apology("Too many shares", 400)
        else:
            # Update balance
            if sell_balance_counter == int(shar_sell):
                db.execute("DELETE FROM balance WHERE user_id=? AND symbol=? AND name=?",\
                                session["user_id"], \
                                sell_comp_quote["symbol"], \
                                sell_comp_quote["name"] )
            else:
                db.execute("UPDATE balance SET shares = ? WHERE name=? AND symbol=? AND user_id=?",\
                                sell_balance_counter - int(shar_sell), \
                                sell_comp_quote["name"], \
                                sell_comp_quote["symbol"], \
                                session["user_id"] )

            # Update cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", \
                            float(sell_usr_cash) + (int(shar_sell) * float(sell_comp_quote["price"])),\
                            session["user_id"] )

            # Update history
            db.execute("INSERT INTO history (user_id, name, symbol, shares, price, total, date) \
                            VALUES (?, ?, ?, ?, ?, ?, ?)", \
                            session["user_id"], \
                            sell_comp_quote["name"], \
                            sell_comp_quote["symbol"], \
                            int(shar_sell) * (-1), \
                            sell_comp_quote["price"], \
                            sell_comp_quote["price"] * int(shar_sell), \
                            datetime.datetime.now() )

            flash("Sold!")
            return redirect("/")
    else:
        return render_template("sell.html", symbols=sell_symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
