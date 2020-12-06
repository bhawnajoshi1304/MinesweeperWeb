from flask import Blueprint, request, render_template, redirect, url_for, flash
from . import db
from werkzeug.security import generate_password_hash, check_password_hash
from .models import User
from flask_login import login_user, logout_user, login_required

auth = Blueprint('auth', __name__)

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

@auth.route('/login')
def login():
    email = request.form.get('email')
    password = request.form.get('password')
    remember = True if request.form.get('remember') else False

    user = User.query.filter_by(email=email).first()

    if not user or not check_password_hash(user.password, password):
        flash("Please check your login details and try again.")
        return redirect(url_for('auth.login'))

    load_user(user,remember=remember)
    return redirect(url_for('main.profile'))
    
@auth.route('/signup', methods=['POST','GET'])
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
            return redirect('auth.signup')

        new_user = User(email=email, name=name, password=generate_password_hash(password, method='sha256'))

        db.session.add(new_user)
        db.session.commit()

        return redirect(url_for('auth.login'))
    else:
        return render_template('signup.html')

@auth.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('main.index'))