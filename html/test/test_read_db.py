import sqlite3

with sqlite3.connect("sqlite.db") as conn:
    print(type(conn))

    cur = conn.cursor()

    cur.execute("""SELECT * FROM mode""")
    print(cur.fetchall())