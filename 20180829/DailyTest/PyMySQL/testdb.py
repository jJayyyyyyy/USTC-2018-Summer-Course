import mysql.connector, logging, datetime

def doSQL(sql, args=''):
	res = None
	try:
		conn = mysql.connector.connect(user='xxx', password='yyy', database='zzz')
		cursor = conn.cursor()
		cursor.execute(sql)
		if args == 'retrieve':
			res = cursor.fetchall()

		conn.commit()
	except Exception as e:
		logging.exception(e)
	finally:
		cursor.close()
		conn.close()

	return res

def initdb():
	sql = 'drop table if exists menu'
	doSQL(sql)
	sql = 'create table menu (menu_id int primary key not null, menu_name varchar(40) not null, menu_date date not null);'
	doSQL(sql)
	sql = "insert into menu values(1, 'hello', '20180825')"
	doSQL(sql)

# CRUD

def create():
	print('\n---------before insert:---------')
	retrieve()

	sql = "insert into menu values (2, 'zzz', '20180827')"
	doSQL(sql);

	print('\n---------after insert:---------')
	retrieve()
	print('\n\n')

def retrieve():
	sql = 'select * from menu'
	res = doSQL(sql, 'retrieve')
	for record in res:
		for column in record:
			print(str(column), end='\t\t')
		print()

def update():
	print('\n---------before update:---------')
	retrieve()

	sql = "update menu set menu_date = '20180829' where menu_id = 2"
	doSQL(sql)

	print('\n---------after update:---------')
	retrieve()
	print('\n\n')

def delete():
	print('\n---------before delete:---------')
	retrieve()

	sql = "delete from menu where menu_id = 2"
	doSQL(sql)
	
	print('\n---------after delete:---------')
	retrieve()

	print('\n\n')

if __name__ == '__main__':
	initdb()

	create()

	update()

	delete()