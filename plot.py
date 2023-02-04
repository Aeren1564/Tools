from matplotlib import pyplot as plt

updates = {
	'point': {'X': [], 'Y': []},
	'polygon': [],
	'polyline': [],
	'circle': [],
}

while True:
	mode = input("> Type\n> '0' or 'show' to show the plot,\n> '1' or 'point' to add points,\n> '2' or 'line' to add lines,\n> '3' or 'polygon' to add polygons,\n> '4' or 'polyline' to add polylines,\n> '5' or 'circle' to add circles,\n> '-1' or 'clear' to empty the plot\n> ")

	if mode == '-1' or mode == 'clear':
		updates['point']['X'].clear()
		updates['point']['Y'].clear()
		updates['polygon'].clear()
		updates['polyline'].clear()
		updates['circle'].clear()

	elif mode == '0' or mode == 'show':
		for name, update in updates.items():
			if name == 'point':
				x = update['X']
				y = update['Y']
				plt.scatter(x, y)
				z = 0
				for i, j in zip(x, y):
					plt.annotate(chr(ord('0') + z), (i, j))
					z += 1
			elif name == 'polygon':
				for p in update:
					x, y = zip(*p)
					plt.plot(x, y)
					z = 0
					for i, j in zip(x, y):
						if z != len(x) - 1:
							plt.annotate(chr(ord('0') + z), (i, j))
						z += 1
			elif name == 'polyline':
				for p in update:
					x, y = zip(*p)
					plt.plot(x, y)
					z = 0
					for i, j in zip(x, y):
						plt.annotate(chr(ord('0') + z), (i, j))
						z += 1
			elif name == 'circle':
				z = 0
				for x, y, r in update:
					plt.gca().add_patch(plt.Circle((x, y), r, fill = False))
					plt.annotate(chr(ord('0') + z), (x, y))
					z += 1
			else:
				pass
		plt.show()

	elif mode == '1' or mode == 'point':
		n = int(input('> # of points: '))
		for i in range(n):
			x, y = [float(v) for v in input('> x y: ').split(' ')]
			updates['point']['X'].append(x)
			updates['point']['Y'].append(y)

	elif mode == '2' or mode == 'line':
		n = int(input('> # of lines: '))
		for i in range(n):
			x0, y0, x1, y1 = [float(v) for v in input('> x0 y0 x1 y1: ').split(' ')]
			updates['polyline'].append([(x0, y0), (x1, y1)]);

	elif mode == '3' or mode == 'polygon':
		n = int(input('> # of polygons: '))
		for i in range(n):
			m = int(input('> # of vertices: '))
			p = []
			for j in range(m):
				x, y = [float(v) for v in input('> x y: ').split(' ')]
				p.append((x, y))
			p.append(p[0])
			updates['polygon'].append(p)

	elif mode == '4' or mode == 'polyline':
		n = int(input('> # of polylines: '))
		for i in range(n):
			m = int(input('> # of vertices: '))
			p = []
			for j in range(m):
				x, y = [float(v) for v in input('> x y: ').split(' ')]
				p.append((x, y))
			updates['polyline'].append(p)

	elif mode == '5' or mode == 'circle':
		n = int(input('> # of circles: '))
		for i in range(n):
			x, y, r = [float(v) for v in input('> x y r: ').split(' ')]
			updates['circle'].append((x, y, r))
	print('>')