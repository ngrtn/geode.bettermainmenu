class CustomMainMenuButton : public geode::GeodeMod {
public:
    void onLoad() override {
        Mod::get()->hook(
            &MenuLayer::init,
            [this](auto self) {
                if (!MenuLayer::init(self)) return false;

                auto btnSpr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
                auto btn = CCMenuItemSpriteExtra::create(
                    btnSpr, this, menu_selector(CustomMainMenuButton::openCustomMenu)
                );
                btn->setPosition({ 180.f, 120.f });
                self->getChildByID("bottom-left-menu")->addChild(btn);

                return true;
            }
        );
    }

    void openCustomMenu(CCObject*) {
        CCDirector::sharedDirector()->pushScene(
            CCTransitionFade::create(0.2f, CustomMenuLayer::scene())
        );
    }
};


class ChangeMenuSongLayer : public CCLayer {
public:
    static CCScene* scene() {
        auto layer = ChangeMenuSongLayer::create();
        auto scene = CCScene::create();
        scene->addChild(layer);
        return scene;
    }

    bool init() override {
        if (!CCLayer::init()) return false;

        auto title = CCLabelBMFont::create("Change Menu Song", "bigFont.fnt");
        title->setPosition({ 240.f, 280.f });
        this->addChild(title);

        auto fromDeviceBtn = CCMenuItemFont::create("Song from device", this, menu_selector(ChangeMenuSongLayer::onFromDevice));
        auto fromNGBtn     = CCMenuItemFont::create("Newgrounds", this, menu_selector(ChangeMenuSongLayer::onNewgrounds));
        auto fromLinkBtn   = CCMenuItemFont::create("From link", this, menu_selector(ChangeMenuSongLayer::onFromLink));

        auto settingsLabel = CCLabelBMFont::create("Settings", "bigFont.fnt");
        settingsLabel->setPosition({ 240.f, 160.f });
        this->addChild(settingsLabel);

        auto monoStereoToggle = CCMenuItemToggle::createWithTarget(this,
            menu_selector(ChangeMenuSongLayer::onToggleMonoStereo),
            CCMenuItemFont::create("Mono"),
            CCMenuItemFont::create("Stereo"),
            nullptr
        );

        auto copyToggle = CCMenuItemFont::create("Use copy of song", this, menu_selector(ChangeMenuSongLayer::onUseCopy));
        auto restartBtn = CCMenuItemFont::create("Restart Game", this, menu_selector(ChangeMenuSongLayer::onRestart));

        auto menu = CCMenu::create(fromDeviceBtn, fromNGBtn, fromLinkBtn, monoStereoToggle, copyToggle, restartBtn, nullptr);
        menu->alignItemsVerticallyWithPadding(10.f);
        menu->setPosition({ 240.f, 200.f });

        this->addChild(menu);

        return true;
    }

    void onFromDevice(CCObject*) {
    }

    void onNewgrounds(CCObject*) {
    }

    void onFromLink(CCObject*) {
    }

    void onToggleMonoStereo(CCObject*) {
    }

    void onUseCopy(CCObject*) {
    }

    void onRestart(CCObject*) {
        GameManager::sharedState()->reloadAll();
    }
};
