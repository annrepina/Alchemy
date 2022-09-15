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

EffectBuilder::EffectBuilder() : Builder()
{
}

void EffectBuilder::setName(string name)
{
	this->element->setName(name);
}

void EffectBuilder::setIsPositive(bool isPositive)
{
	this->element->setIsPositive(isPositive);
}

void EffectBuilder::buildEffect(int lastIndex, bool IsPositive)
{
	if (IsPositive)
		buildEffect(lastIndex, listOfPositiveEffectsNames, POSITIVE);

	else
		buildEffect(lastIndex, listOfNegativeEffectsNames, NEGATIVE);
}

void EffectBuilder::buildEffect(int lastIndex, string listOfEffects[], bool isPositive)
{
	// Выбираем рандомно имя
	string name = chooseEffectName(lastIndex, listOfEffects);

	// Устанавливаем имя
	setName(name);

	// Говорим, что эффект позитивный
	setIsPositive(isPositive);
}

string EffectBuilder::chooseEffectName(int lastIndex, string listOfEffectsNames[])
{
	// Рандомно выбираем имя из списка
	int numberOfName = randInRange(0, lastIndex);

	// Присваиваем строке выбранное имя
	string name = listOfEffectsNames[numberOfName];

	// Свопаем выбранный и последний элемент
	swap(listOfEffectsNames[numberOfName], listOfEffectsNames[lastIndex]);

	// Возвращаем имя
	return name;
}