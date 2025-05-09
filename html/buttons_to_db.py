import sys
import sqlite3

with sqlite3.connect("sqlite.db") as conn:
    print(type(conn))

    cur = conn.cursor()

    cur.execute("""CREATE TABLE IF NOT EXISTS mode(mode);""")
    cur.execute("""DELETE FROM mode""")

    for arg in sys.argv:

        if arg == "auto":
            cur.execute("""INSERT INTO mode (mode) VALUES (?)""",(1,))
            conn.commit()
        
        elif arg == "manual":
            cur.execute("""INSERT INTO mode (mode) VALUES (?)""",(0,))
            conn.commit()
