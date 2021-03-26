class Rect:
	x = 0
	y = 0
	width = 0
	height = 0

	def __init__(self, x, y, width, height):
		self.x = x
		self.y = y
		self.width = width
		self.height = height

	def __repr__(self):
		return str(self.x) + " " + str(self.y) + " " + str(self.width) + " " + str(self.height)


def is_prime(N):
	return N in [2, 3, 5, 7, 11, 13, 17, 19]


def create_square(free_rect, square_size):
	right_down_corner = (free_rect.x+free_rect.width, free_rect.y+free_rect.height)
	new_rect_x = right_down_corner[0]-square_size
	new_rect_y = right_down_corner[1]-square_size
	new_rect_coord = (new_rect_x, new_rect_y)
	new_rect = Rect(new_rect_coord[0], new_rect_coord[1], square_size, square_size)
	return new_rect


def find_free_rect(N, squares, y_min):
	max_value = max(y_min)
	max_index = y_min.index(max_value)

	count = 0

	for i in range(max_index, len(y_min)):
		if y_min[i] != max_value:
			break
		count += 1

	return Rect(max_index, 0, count, max_value)


def init_squares(N):
	return [Rect(int(N/2), int(N/2), int(N/2+1), int(N/2+1)), Rect(0, int(N/2+1), int(N/2), int(N/2)), Rect(int(N/2+1), 0, int(N/2), int(N/2))]


def solve(N, squares=[], y_min=[]):
	global min_solution
	if not y_min:
		y_min = [N]*(N)

	if not squares and is_prime(N): 
		squares = init_squares(N)
		y_min = [int(N/2+1)]*int(N/2) + [int(N/2)] + [0]*int(N/2) 

	free_rectangle = find_free_rect(N, squares, y_min)

	if free_rectangle.height == 0:
		if not min_solution:
			min_solution = (squares)
		if len(min_solution) > len(squares):
			min_solution = squares
		return


	if min_solution and len(min_solution) <= len(squares):
		return

	square_size = min(free_rectangle.width, free_rectangle.height)

	square_width_range = ()
	if not squares: 
		square_width_range = range(int((N+1)/2), square_size)
	else:
		square_width_range = range(square_size, 0, -1)


	for width in square_width_range:
		new_square = create_square(free_rectangle, width)
		solve(N, squares[:] + [new_square], y_min[0:new_square.x] + [new_square.y]*(new_square.width) + y_min[new_square.x+new_square.width:])


min_solution = []


N = int(input())
solve(N)

print(len(min_solution))
for i in min_solution:
	print(i.x, i.y, i.width)