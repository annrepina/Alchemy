#include "IngredientBuilder.h"
#include "ServiceFunctions.h"

string IngredientBuilder::listOfIngredientsNames[NUMBER_OF_INGREDIENTS] = {
	"Абесинский окунь",
	"Алый корень Нирна",
	"Белянка",
	"Бесовский гриб",
	"Бойцовая рыбка",
	"Болотный стручок",
	"Большие рога",
	"Бородатый мох",
	"Вересковое сердце",
	"Ветка чертополоха",
	"Виноград Джазби",
	"Гигантский лишайник",
	"Глаз саблезуба",
	"Гниль Намиры",
	"Голубой горноцвет",
	"Двемерское масло",
	"Жареная злокрысья кожа",
	"Жемчужина",
	"Живица сприггана",
	"Жир тролля",
	"Зубы ледяного привидения",
	"Икра рыбы-убийцы",
	"Корень Нирна",
	"Красный горноцвет",
	"Клешня грязевого краба",
	"Клык саблезуба",
	"Клюв ястреба",
	"Коготь ворожеи",
	"Костная мука",
	"Кровавый венец",
	"Крыло лунного мотылька",
	"Крыло монарха",
	"Крыло синей бабочки",
	"Куриное яйцо",
	"Лаванда",
	"Лиловый горноцвет",
	"Лунный сахар",
	"Лютый гриб",
	"Маленькая жемчужина",
	"Маленькие рога",
	"Медвежьи когти",
	"Медовые соты",
	"Мора тапинелла",
	"Морозная мириам",
	"Морозная соль",
	"Морской жёлудь",
	"Мухомор",
	"Огненная соль",
	"Оранжевая стрекоза",
	"Палец великана",
	"Паслён",
	"Паучье яйцо",
	"Пелена дымка",
	"Перья ворожеи",
	"Перья ястреба",
	"Ползучая лоза",
	"Прах вампира",
	"Пушица",
	"Пчела",
	"Пчелиное гнездо",
	"Пшеница",
	"Светящаяся пыль",
	"Светящийся гриб",
	"Сердце даэдра",
	"Серебристый окунь",
	"Синяя стрекоза",
	"Сиродильский лопатохвост",
	"Снежные ягоды",
	"Собачий корень",
	"Соль",
	"Соль пустоты",
	"Стержневой корень",
	"Толчёный бивень мамонта",
	"Торакс светлячка",
	"Травяной стручок",
	"Ухо фалмера",
	"Хвост злокрыса",
	"Хисткарп",
	"Человеческое сердце",
	"Человечье мясо",
	"Чеснок",
	"Чешуйчатка",
	"Чешуя рыбы-убийцы",
	"Эктоплазма",
	"Эльфийское ухо",
	"Ягоды можжевельника",
	"Ядовитый колокольчик",
	"Язык дракона",
	"Яйцо коруса",
	"Яйцо оригмы",
	"Яйцо соснового дрозда",
	"Жёлтый горноцвет",
	"Крыло мотылька предка",
	"Светящийся цветок",
	"Ядовитый цветок",
	"Лососёвая икра",
	"Яйцо ястреба",
	"Вредозобник",
	"Желе нетча",
	"Пепел порождения",
};

IngredientBuilder::IngredientBuilder() : Builder()
{
	//reset();

	this->effectsTable = nullptr;
}

//IngredientBuilder::~IngredientBuilder()
//{
//	clear();
//}

void IngredientBuilder::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

int IngredientBuilder::getEffectsTableSize()
{
	return this->effectsTable->getSize();
}

EffectsTable* IngredientBuilder::getEffectsTable()
{
	return this->effectsTable;
}

void IngredientBuilder::buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex)
{
	string name = chooseIngredientName(lastIngredientNameIndex);

	setName(name);

	int price = randInRange(MIN_PRICE, MAX_PRICE);

	setPrice(price);

	// Создаем вектор id эффектов
	vector<int> tempEffectsId;

	// Добавление эффектов
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, --lastEffectIndex)
	{
		// если закончились эффекты, то начинаем сначала
		if (0 == lastEffectIndex)
			lastEffectIndex = this->getEffectsTableSize() - 1;

		int idIndex = randInRange(0, lastEffectIndex);

		// если это уже не первый эффект
		if (0 < i)
		{
			// Проверяем не добавлялся ли такой же до этого
			if (find(tempEffectsId.begin(), tempEffectsId.end(), this->effectsId[idIndex]) != tempEffectsId.end())
			{
				--i;
				++lastEffectIndex;
				continue;
			}
		}

		// Добавляем во временный вектор id
		tempEffectsId.push_back(effectsId[idIndex]);

		// Добавляем id к вектору основному
		addEffect(effectsId[idIndex]);

		// Свопаем элементы в векторе
		swap(this->effectsId[idIndex], this->effectsId[lastEffectIndex]);
	}
}

void IngredientBuilder::setName(string name)
{
	this->element->setName(name);
}

void IngredientBuilder::setPrice(int price)
{
	this->element->setPrice(price);
}

void IngredientBuilder::addEffect(int effectId)
{
	this->element->addEffect(effectId);
}

//Ingredient* IngredientBuilder::getResult()
//{
//	Ingredient* result = this->ingredient;
//
//	reset();
//
//	return result;
//}

string IngredientBuilder::chooseIngredientName(int lastIndex)
{
	// Рандомно выбираем имя из списка
	int numberOfName = randInRange(0, lastIndex);

	// Присваиваем строке выбранное имя
	string name = listOfIngredientsNames[numberOfName];

	// Свопаем выбранный и последний элемент
	swap(listOfIngredientsNames[numberOfName], listOfIngredientsNames[lastIndex]);

	// Возвращаем имя
	return name;
}

//void IngredientBuilder::reset()
//{
//	this->ingredient = new Ingredient();
//}
//
//void IngredientBuilder::clear()
//{
//	if (this->ingredient != nullptr)
//	{
//		delete this->ingredient;
//		this->ingredient = nullptr;
//	}
//}

void IngredientBuilder::fillEffectId()
{
	int size = this->effectsTable->getSize();

	for (int i = 1; i <= size; ++i)
	{
		this->effectsId.push_back(i);
	}
}
