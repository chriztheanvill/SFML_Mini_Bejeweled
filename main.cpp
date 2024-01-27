#include <SFML/Graphics.hpp>
#include <ctime>
#include <fmt/core.h>
#include <iostream>

constexpr int ts { 54 };		 // Tile Size
constexpr int tileSize { 49 };	 // Tile Size
sf::Vector2i offset { 48, 24 };

struct piece
{
  int x;
  int y;
  int col;
  int row;
  int kind;
  int match;
  // bool swapped { };

  piece( ) { match = 0; }
} grid[10][10];

auto Swap(piece p1, piece p2) -> void
{
  std::swap(p1.col, p2.col);
  std::swap(p1.row, p2.row);

  grid[p1.row][p1.col] = p1;
  grid[p2.row][p2.col] = p2;
}

int main( )
{
  srand(time(nullptr));

  sf::RenderWindow app(sf::VideoMode(740, 480), "Bejeweled");
  app.setFramerateLimit(60);

  sf::Texture t1, t2;
  t1.loadFromFile("Assets/background.png");
  t2.loadFromFile("Assets/gems.png");

  sf::Sprite background(t1), gems(t2);

  // Set grid values
  for (int row = 1; row <= 8; ++row)
  {
	for (int col = 1; col <= 8; ++col)
	{
	  grid[row][col].kind = rand( ) % 7;
	  grid[row][col].col = col;
	  grid[row][col].row = row;
	  grid[row][col].x = col * ts;
	  grid[row][col].y = row * ts;
	}
  }

  int x0, y0, x, y;
  int click = 0;
  sf::Vector2i pos;
  bool isSwap { };
  bool isMoving { };

  // ################################
  while (app.isOpen( ))
  {
	sf::Event e;
	while (app.pollEvent(e))
	{
	  if (e.type == sf::Event::Closed) app.close( );
	  if (e.type == sf::Event::MouseButtonPressed)
		if (e.key.code == sf::Mouse::Left)
		{
		  if (!isSwap && !isMoving) click++;
		  pos = sf::Mouse::getPosition(app) - offset;
		}
	}

	// Mouse Click
	if (click == 1)
	{
	  x0 = pos.x / ts + 1;
	  y0 = pos.y / ts + 1;
	}
	if (click == 2)
	{
	  x = pos.x / ts + 1;
	  y = pos.y / ts + 1;

	  //
	  if (abs(x - x0) + abs(y - y0) == 1)
	  {
		Swap(grid[y0][x0], grid[y][x]);
		// grid[y0][x0].swapped = true;
		// grid[y][x].swapped = true;
		click = 0;
		isSwap = true;
	  }
	  else click = 1;
	}

	// Match
	// Set grid values
	for (int row = 1; row <= 8; ++row)
	{
	  for (int col = 1; col <= 8; ++col)
	  {
		if (grid[row][col].kind == grid[row + 1][col].kind)
		  if (grid[row][col].kind == grid[row - 1][col].kind)
			for (int n = -1; n <= 1; n++) { grid[row + n][col].match++; }
		if (grid[row][col].kind == grid[row][col + 1].kind)
		  if (grid[row][col].kind == grid[row][col - 1].kind)
			for (int n = -1; n <= 1; n++) { grid[row][col + n].match++; }
	  }
	}

	/*
	 * Moving Animation
	 * No termina en los for, cada iteracion de while ayuda a terminar
	 * hasta que no sea 0 dx y dy
	 */
	isMoving = false;
	for (int i = 1; i <= 8; ++i)
	{
	  for (int j = 1; j <= 8; ++j)
	  {
		piece& p = grid[i][j];
		// if (!p.swapped) continue;

		int dx, dy;

		for (int n = 0; n < 5; ++n)
		{
		  dx = p.x - p.col * ts;
		  dy = p.y - p.row * ts;
		  // std::cout << "\n dx" << dx;
		  // std::cout << "\n dy" << dy;
		  if (dx) p.x -= dx / abs(dx);
		  if (dy) p.y -= dy / abs(dy);
		}
		if (dx || dy) isMoving = true;
		// if (dx == 0 && dy == 0) p.swapped = false;
	  }
	}

	int score { };
	for (int i = 1; i <= 8; ++i)
	{
	  for (int j = 1; j <= 8; ++j) { score += grid[i][j].match; }
	}

	if (isSwap && !isMoving)
	{
	  if (!score) Swap(grid[y0][x0], grid[y][x]);
	  isSwap = false;
	}

	if (!isMoving)
	{
	  for (int i = 8; i > 0; i--)
	  {
		for (int j = 1; j <= 8; ++j)
		  if (grid[i][j].match)
			for (int n = i; n > 0; n--)
			{
			  if (!grid[n][j].match)
			  {
				Swap(grid[n][j], grid[i][j]);
				break;
			  }
			}
	  }

	  for (int j = 1; j <= 8; j++)
	  {
		for (int i = 8, n = 0; i > 0; i--)
		  if (grid[i][j].match)
		  {
			grid[i][j].kind = rand( ) % 7;
			grid[i][j].y = -ts * n++;
			grid[i][j].match = 0;
		  }
	  }
	}

	// DRAW
	app.draw(background);

	for (int i = 1; i <= 8; ++i)
	{
	  for (int j = 1; j <= 8; ++j)
	  {
		piece p = grid[i][j];
		gems.setTextureRect(
		  sf::IntRect(p.kind * tileSize, 0, tileSize, tileSize)
		);
		gems.setPosition(p.x, p.y);
		gems.move(offset.x - ts, offset.y - ts);
		app.draw(gems);
	  }
	}

	app.display( );
  }

  return 0;
}