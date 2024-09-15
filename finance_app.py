import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # User stocks and shares
    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
                        user_id=session["user_id"])

    # User cashbalance
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                      user_id=session["user_id"])[0]["cash"]

    # Variables for total values
    total_value = cash
    grand_total = cash

    # Ietarte over stocks, prive and value
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    return render_template("index.html", stocks=stocks, cash=cash, total_value=total_value, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("Provide a symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Must provide a positive integer or symbol")

        quote = lookup(symbol)
        if quote is None:
            return apology("Missing symbol")

        price = quote["price"]
        total_cost = int(shares) * price
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                          user_id=session["user_id"])[0]["cash"]

        if cash < total_cost:
            return apology("You need more cash")

        # Update users table
        db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
                   total_cost=total_cost, user_id=session["user_id"])

        # Add purchase
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=symbol, shares=shares, price=price)

        flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Query for transactions
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC", user_id=session["user_id"])

    # Render history
    return render_template("history.html", transactions=transactions)
    return apology("TODO")


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Invalid symbol", 400)
        return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget user id
    session.clear()
    # User reached route
    if request.method == "POST":
        # Ensure username
        if not request.form.get("username"):
            return apology("Please provide username", 400)
        # Ensure password
        elif not request.form.get("password"):
            return apology("Please provide password", 400)
        # Password confirmation
        elif not request.form.get("confirmation"):
            return apology("Please confirm password", 400)
        # Match password confirmation
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password do not match", 400)
        # Query database
        rows = db.execute("SELECT *FROM users WHERE username = ?", request.form.get("username"))

        # Ensure existence username
        if len(rows) != 0:
            return apology("Username in use", 400)
        # Insert new user
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                   request.form.get("username"), generate_password_hash(request.form.get("password")))
        # Query for new username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        # Remember user logged in
        session["user_id"] = rows[0]["id"]
        # Redirect to homepage
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Get user stocks
    stocks = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
                        user_id=session["user_id"])

    # User submits the form
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        if not symbol:
            return apology("Provide a symbol")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("Provide a positive integer or share")
        else:
            shares = int(shares)

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("not enogh shares")
                else:
                    # Get quote
                    quote = lookup(symbol)
                    if quote is None:
                        return apology("Symbol not found")
                    price = quote["price"]
                    total_sale = shares * price

                    # Update users table
                    db.execute("UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                               total_sale=total_sale, user_id=session["user_id"])
                    # Add the sale to history
                    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                               user_id=session["user_id"], symbol=symbol, shares=shares, price=price)

                    flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}!")
                    return redirect("/")

        return apology("Symbol not found")

    # If the user visit the page
    else:
        return render_template("sell.html", stocks=stocks)