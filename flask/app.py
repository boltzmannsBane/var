from flask import Flask, render_template_string
import mysql.connector
import yaml

app = Flask(__name__)

# Read configuration from YAML file
with open("config.yaml", 'r') as ymlfile:
    config = yaml.safe_load(ymlfile)

# Connect to MySQL database
db_config = config['database']
cnx = mysql.connector.connect(**db_config)

# Define HTML template
template = '''
<!DOCTYPE html>
<html>
<head>
    <title>{{ title }}</title>
</head>
<body>
    <h1>{{ header }}</h1>
    <ul>
        {% for item in data %}
            <li>{{ item }}</li>
        {% endfor %}
    </ul>
</body>
</html>
'''
@app.route('/ping')
def ping():
    return render_template_string(template, title='Hello World!', header='Runnng')

@app.route('/endpoint1')
def endpoint1():
    cursor = cnx.cursor()
    cursor.execute('SELECT name FROM table1')
    data = [row[0] for row in cursor.fetchall()]
    return render_template_string(template, title='Endpoint 1', header='Data from table1', data=data)

@app.route('/endpoint2')
def endpoint2():
    cursor = cnx.cursor()
    cursor.execute('SELECT name FROM table2')
    data = [row[0] for row in cursor.fetchall()]
    return render_template_string(template, title='Endpoint 2', header='Data from table2', data=data)

if __name__ == '__main__':
    app.run(port=5000)
