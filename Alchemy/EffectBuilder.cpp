#include "EffectBuilder.h"
#include "ServiceFunctions.h"

string EffectBuilder::listOfPositiveEffectsNames[NUMBER_OF_POSITIVE_EFFECTS] = {
	"Водное дыхание",
	"Восстановление запаса сил",
	"Восстановление здоровья",
	"Восстановление магии",
	"Исцеление болезней",
	"Невидимость",
	"Повышение запаса сил",
	"Повышение здоровья",
	"Повышение магии",
	"Повышение искусства торговли",
	"Повышение навыка: блокирование",
	"Повышение навыка: взлом",
	"Повышение навыка: восстановление",
	"Повышение навыка: двуручное оружие",
	"Повышение навыка: зачарование",
	"Повышение навыка: изменение",
	"Повышение навыка: иллюзия",
	"Повышение навыка: карманные кражи",
	"Повышение навыка: колдовство",
	"Повышение навыка: кузнечное дело",
	"Повышение навыка: лёгкая броня",
	"Повышение навыка: одноручное оружие",
	"Повышение навыка: разрушение",
	"Повышение навыка: скрытность",
	"Повышение навыка: стрельба",
	"Повышение навыка: тяжёлая броня",
	"Повышение переносимого веса",
	"Регенерация запаса сил",
	"Регенерация здоровья",
	"Регенерация магии",
	"Сопротивление магии",
	"Сопротивление огню",
	"Сопротивление холоду",
	"Сопротивление электричеству",
	"Сопротивление ядам",
};

string EffectBuilder::listOfNegativeEffectsNames[NUMBER_OF_NEGATIVE_EFFECTS] = {
	"Бешенство",
	"Замедление",
	"Затяжной урон запасу сил",
	"Затяжной урон здоровью",
	"Затяжной урон магии",
	"Опустошение запаса сил",
	"Опустошение здоровья",
	"Опустошение магии",
	"Паралич",
	"Повреждение регенерации запаса сил",
	"Повреждение регенерации магии",
	"Страх",
	"Урон запасу сил",
	"Урон здоровью",
	"Урон магии",
	"Уязвимость к магии",
	"Уязвимость к огню",
	"Уязвимость к холоду",
	"Уязвимость к электричеству",
	"Уязвимость к яду",
};

EffectBuilder::EffectBuilder()
{
	reset();
}

EffectBuilder::~EffectBuilder()
{
	clear();
}

void EffectBuilder::setName(string name)
{
	this->effect->setName(name);
}

void EffectBuilder::setIsPositive(bool isPositive)
{
	this->effect->setIsPositive(isPositive);
}

void EffectBuilder::buildEffect(int lastIndex, string listOfEffectsNames[], bool isPositive)
{
	// Выбираем рандомно имя
	string name = chooseEffectName(lastIndex, listOfEffectsNames);

	// Устанавливаем имя
	setName(name);

	// Говорим, что эффект позитивный
	setIsPositive(isPositive);
}

void EffectBuilder::buildPositiveEffect(int lastIndex)
{
	// Выбираем рандомно имя
	string name = chooseEffectName(lastIndex, listOfPositiveEffectsNames);

	// Устанавливаем имя
	setName(name);

	// Говорим, что эффект позитивный
	setIsPositive(true);
}

void EffectBuilder::buildNegativeEffect(int lastIndex)
{
	// Выбираем рандомно имя
	string name = chooseEffectName(lastIndex, listOfNegativeEffectsNames);

	// Устанавливаем имя
	setName(name);

	// Говорим, что эффект позитивный
	setIsPositive(false);
}

Effect* EffectBuilder::getResult()
{
	Effect* res = this->effect;

	reset();

	return res;
}

void EffectBuilder::reset()
{
	effect = new Effect;
}

void EffectBuilder::clear()
{
	if (nullptr != this->effect)
	{
		delete this->effect;
		this->effect = nullptr;
	}
}

string EffectBuilder::chooseEffectName(int lastIndex, string listOfEffectsNames[])
{
	// Рандомно выбираем имя из списка
	int NumberOfName = randInRange(0, lastIndex);

	// Присваиваем строке выбранное имя
	string name = listOfEffectsNames[NumberOfName];

	// Свопаем выбранный и последний элемент
	swap(listOfEffectsNames[NumberOfName], listOfEffectsNames[lastIndex]);

	// Возвращаем имя
	return name;
}


