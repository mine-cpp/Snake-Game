#include <window.hpp>



void window::clear() const {
	SDL_RenderClear(this->ren);
}

void window::clear(const int r, const int g, const int b) const {
	SDL_SetRenderDrawColor(this->ren, r, g, b, 255);
	SDL_RenderClear(this->ren);
}

void window::clear(const int r, const int g, const int b, const int a) const {
	SDL_SetRenderDrawColor(this->ren, r, g, b, a);
	SDL_RenderClear(this->ren);
}

void window::render(const image& img) const {
	SDL_Rect src = img.get_src(),
		des = img.get_des();
	SDL_RenderCopy(this->ren, img.get_img(), &src, &des);
}

void window::render(const snake& snk, const map& tile_map) const {
	const std::string lvl = tile_map.get_lvl();
	char tile;

	const int w = tile_map.get_w(),
		h = tile_map.get_h(),
		tw = tile_map.get_tw(),
		th = tile_map.get_th();

	SDL_Rect src, des;

	for (int y = 0; y < h; ++y) {

		for (int x = 0; x < w; ++x) {
			src = { 16, 0, 8, 8 };
			des = { x * tw, y * th, tw, th };
			SDL_RenderCopy(this->ren, snk.get_spr()->get_img(), &src, &des);

			tile = lvl[y * w + x];

			if (tile == 'O') {
				src = { 8, 0, 8, 8 };
				des = { x * tw, y * th, tw, th };
				SDL_RenderCopy(this->ren, snk.get_spr()->get_img(), &src, &des);

			}

		}

	}

	for (unsigned i = 0; i < snk.num_pos(); ++i) {

		vec2f pos = snk.get_pos(i);
		int x = pos.x,
			y = pos.y;

		src = { 0, 0, 8, 8 };
		des = { x, y, tw, th };
		SDL_RenderCopy(this->ren, snk.get_spr()->get_img(), &src, &des);

	}

}

void window::update() const {
	SDL_RenderPresent(this->ren);
}