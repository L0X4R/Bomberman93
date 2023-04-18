#include "TextManager.h"
#include "config.h"

TextManager* TextManager::pInstance = NULL;

TextManager::TextManager()
{
	font = nullptr;

	int TTF_Result = TTF_Init();

	vm = VideoManager::getInstance();

	if (vm != nullptr && TTF_Result == 0)
	{
		GOOD("GESTOR DE TEXTOS CREADO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CARGAR EL GESTOR DE TEXTOS.");
	}
}

TextManager::~TextManager()
{
}

void TextManager::setFont(int size, const char* fontPath)
{
	if (font != nullptr)
	{
		delete font;
		font = nullptr;
	}

	font = TTF_OpenFont(fontPath, size);
}

void TextManager::DrawText(string text, rect textRect, int R, int G, int B, int A)
{
	SDL_Color color;

	color.r = R;
	color.g = G;
	color.b = B;
	color.a = A;

	SDL_Rect tempRect;

	tempRect.x = textRect.x;
	tempRect.y = textRect.y;
	tempRect.w = textRect.w;
	tempRect.h = textRect.h;

	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(vm->GPU, tempSurface);

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;


	SDL_RenderCopy(vm->GPU, tempTexture, NULL, &tempRect);

	SDL_DestroyTexture(tempTexture);
	tempTexture = nullptr;
}

void TextManager::addReward(int points, rect textRect, int R, int G, int B, int A)
{
	SDL_Color color;

	color.r = R;
	color.g = G;
	color.b = B;
	color.a = A;

	SDL_Rect tempRect;

	tempRect.x = textRect.x + (textRect.w / 2) - 16;
	tempRect.y = textRect.y - 8;
	tempRect.w = 32;
	tempRect.h = 16;

	string pointsFormated = "+" + to_string(points);

	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, pointsFormated.c_str(), color);

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(vm->GPU, tempSurface);

	reward* newReward = new reward;

	newReward->txReward = tempTexture;
	newReward->position = tempRect;
	newReward->alpha = 255;

	scoreRewards.push_back(newReward);

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;
}

void TextManager::renderRewards()
{
	for (int i = 0; i < scoreRewards.size(); i++)
	{
		scoreRewards[i]->remaining -= vm->getDeltaTime();

		if (scoreRewards[i]->remaining >= 0)
		{
			float reduction = ((float)scoreRewards[i]->remaining / (float)scoreRewards[i]->defaultTime);

			float alpha = (float)(255 * reduction);

			vm->changeAlpha(-1, scoreRewards[i]->txReward, alpha);

			scoreRewards[i]->position.y -= 0.005f;

			SDL_Rect worldPos = scoreRewards[i]->position;
			worldPos.x -= Camera.x;

			SDL_RenderCopy(vm->GPU, scoreRewards[i]->txReward, NULL, &worldPos);
		}
		else
		{

			SDL_DestroyTexture(scoreRewards[i]->txReward);
			scoreRewards[i]->txReward = nullptr;
			scoreRewards.erase(scoreRewards.begin() + i);
			i--;
		}
	}
}

TextManager* TextManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new TextManager();
	}

	return pInstance;
}
