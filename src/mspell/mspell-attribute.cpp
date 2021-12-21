#include "mspell/mspell-attribute.h"

AttributeType get_ability_attribute(MonsterAbilityType ability) {
    return Attribute_of_Ability.at(ability);
}
