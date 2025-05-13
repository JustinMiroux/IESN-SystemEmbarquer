import sqlite3

with sqlite3.connect("sqlite.db") as conn:
    print(type(conn))

    cur = conn.cursor()

    cur.execute("""SELECT * FROM mode""")
    test = cur.fetchall()
    testuple = test[0]
    print(type(testuple))
    print(testuple[0])
