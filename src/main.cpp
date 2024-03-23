#pragma region Includes
#include "main.hpp"

// GlobalNamespace
#include "GlobalNamespace/HealthWarningFlowCoordinator.hpp"
#include "GlobalNamespace/PlayerAgreements.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/PlayerDataModel.hpp"
#pragma endregion

#pragma region Usings
using namespace GlobalNamespace;
#pragma endregion

#pragma region Hook definitions
MAKE_HOOK_MATCH(HealthWarningFlowCoordinator_DidActivate, &HealthWarningFlowCoordinator::DidActivate, void, HealthWarningFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    HealthWarningFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    auto flag1 = self->____playerDataModel->get_playerData()->get_playerAgreements()->AgreedToEula();
    auto flag2 = self->____playerDataModel->get_playerData()->get_playerAgreements()->AgreedToPrivacyPolicy();

    if (flag1 && flag2) {
        self->HandleHealthWarningViewControllerDidFinish();
    }
}
#pragma endregion

#pragma region Mod setup
/// @brief Called at the early stages of game loading
/// @param info
/// @return
MOD_EXPORT_FUNC void setup(CModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;

    Logger.info("Completed setup!");
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();

    Logger.info("Installing hooks...");

    INSTALL_HOOK(Logger, HealthWarningFlowCoordinator_DidActivate);

    Logger.info("Installed all hooks!");
}
#pragma endregion
