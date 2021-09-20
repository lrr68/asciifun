struct Pixel {
	int x;
	int y;
};

struct Pixel
new_pixel(int x, int y)
{
	return Pixel {
		.x = x,
		.y = y,
	};
}
