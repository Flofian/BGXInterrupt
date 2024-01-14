#include "plugin_sdk/plugin_sdk.hpp"
namespace interrupt {
    struct interruptableSpell {
        float minRemainingTime;
        float maxRemainingTime;
        float expectedRemainingTime;
        int dangerLevel;
        interruptableSpell() {
            minRemainingTime = 0;
            maxRemainingTime = 0;
            expectedRemainingTime = 0;
            dangerLevel = -1;
        }
    };
    struct internalSpellData {
        float minTime;
        float maxTime;
        float expectedTime;
        float castTime;
        internalSpellData() {
            minTime = 0;
            maxTime = 0;
            expectedTime = 0;
            castTime = 0;
        }
        internalSpellData(float min, float max, float e, float c) {
            minTime = min;
            maxTime = max;
            expectedTime = e;
            castTime = c;
        }
    };  // Code duplication is ugly, i know, but i think that look better
	std::string getDisplayName(game_object_script target);
	void InitializeCancelMenu(TreeTab* tab, bool debugUseAllies=false);
	int getCastingImportance(game_object_script target);
    interruptableSpell getInterruptable(game_object_script target);
}