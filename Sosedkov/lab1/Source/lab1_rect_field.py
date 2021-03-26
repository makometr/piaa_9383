from time import time


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
		return str(self.x) + "," + str(self.y) + "," + str(self.width) + "," + str(self.height)




def create_square(free_rect, square_size):
	right_down_corner = (free_rect.x+free_rect.width, free_rect.y+free_rect.height)
	new_x = right_down_corner[0]-square_size
	new_y = right_down_corner[1]-square_size
	return Rect(new_x, new_y, square_size, square_size)




def find_free_rect(squares, y_min):
	max_value = max(y_min)
	max_index = y_min.index(max_value)

	count = 0

	for i in range(max_index, len(y_min)):
		if y_min[i] != max_value:
			break
		count += 1

	return Rect(max_index, 0, count, max_value)





def update_squares(squares, y_min):
	while squares and squares[-1].width == 1:
		new_square = squares[-1]
		squares.pop()
		y_min = y_min[0:new_square.x] + [new_square.y+new_square.height]*(new_square.width) + y_min[new_square.x+new_square.width:]


	if not squares: return ([],[])

	new_square = squares[-1]
	squares.pop()
	y_min = y_min[0:new_square.x] + [new_square.y+new_square.height]*(new_square.width) + y_min[new_square.x+new_square.width:]
	free_rectangle = find_free_rect(squares, y_min)

	new_square = create_square(free_rectangle, new_square.width-1)
	
	squares.append(new_square)
	y_min = y_min[0:new_square.x] + [new_square.y]*(new_square.width) + y_min[new_square.x+new_square.width:]

	return (squares, y_min)





def backtracking(W,H):
	y_min = [H]*(W)
	squares = []
	min_solution = []
	count = 1

	while True:
		free_rectangle = find_free_rect(squares, y_min)
		
		if min_solution and len(squares) > len(min_solution):
			squares, y_min = update_squares(squares, y_min)
			if not squares: break

		elif free_rectangle.height > 0:
			square_width = min(free_rectangle.width, free_rectangle.height)
			if not squares: 
				square_width -= 1

			new_square = create_square(free_rectangle, square_width)
			squares.append(new_square)
			y_min = y_min[0:new_square.x] + [new_square.y]*(new_square.width) + y_min[new_square.x+new_square.width:]

		else:
			if not min_solution:
				min_solution = squares[:]
			elif len(min_solution) > len(squares):
				count = 1
				min_solution = squares[:]
			elif len(min_solution) == len(squares):
				count += 1

			squares, y_min = update_squares(squares, y_min)
			if not squares: break

	return (min_solution, count)




if __name__ == '__main__':
	N = int(input())
	M = int(input())

	if N >= 2 and M >= 2:
		start_time = time()

		solution = backtracking(N, M)
		print('Number of squares:', len(solution[0]))
		print('Number of solutions:', solution[1])

		end_time = time()

		print("Time:", end_time-start_time)
	else:
		print('2 <= N,M <= 20')
