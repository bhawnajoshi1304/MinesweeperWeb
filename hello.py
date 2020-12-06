from flask import Flask, Blueprint, request, render_template, redirect, url_for, flash
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import login_user, logout_user, login_required, current_user, LoginManager, UserMixin
from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True) # primary keys are required by SQLAlchemy
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(100))
    name = db.Column(db.String(1000))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret-key-goes-here'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqlite'

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/profile")
@login_required
def profile():
    return render_template('profile.html', name=current_user.name)

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

@app.route('/login')
def login():
    email = request.form.get('email')
    password = request.form.get('password')
    remember = True if request.form.get('remember') else False

    user = User.query.filter_by(email=email).first()

    if not user or not check_password_hash(user.password, password):
        flash("Please check your login details and try again.")
        return redirect(url_for('app.login'))

    load_user(user,remember=remember)
    return redirect(url_for('app.profile'))
    
@app.route('/signup', methods=['POST','GET'])
def signup():
    if request.method == 'POST':
        #request data from form
        email = request.form.get('email')
        name = request.form.get('name')
        password = request.form.get('password')

        #check if user already in database
        user = User.query.filter_by(email=email).first()

        if user:
            flash('E-mail address already exists')
            return redirect('app.signup')

        new_user = User(email=email, name=name, password=generate_password_hash(password, method='sha256'))

        db.session.add(new_user)
        db.session.commit()

        return redirect(url_for('app.login'))
    else:
        return render_template('signup.html')

@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('app.index'))