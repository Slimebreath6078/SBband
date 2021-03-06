#include "store/store-owners.h"
#include "player-info/race-types.h"

/*!
 * @todo _() でまとめる
 */
const owner_type owners[MAX_STORES][MAX_OWNERS] = {
    {
/* General store - 32 unique names */
/*
  Raistlin は dragonlance の powerful wizard 。
  Rincewind the Chicken は Terry Pratchett の Discworld の登場人物 上記のパロディ？、
  { "憶病者ラストリン",  200, 108, PlayerRaceType::HUMAN},
  { "Raistlin the Chicken", 200, 108, PlayerRaceType::HUMAN},
*/
#ifdef JP
        { "フレンドリーなビルボ", 30000, 108, PlayerRaceType::HOBBIT },
        { "憶病者リンスウィンド", 30000, 108, PlayerRaceType::HUMAN },
        { "背の低いサルタン", 30000, 107, PlayerRaceType::GNOME },
        { "ハンサムなライア=エル", 30000, 107, PlayerRaceType::ELF },
        { "親切なファリルマウエン", 30000, 108, PlayerRaceType::HOBBIT },
        { "臆病者ヴォワラン", 30000, 108, PlayerRaceType::HUMAN },
        { "チビのエラシュナク", 30000, 107, PlayerRaceType::BEASTMAN },
        { "ハンサムなグラッグ", 30000, 107, PlayerRaceType::HALF_TITAN },
        { "ケチなフォロビア", 30000, 108, PlayerRaceType::HUMAN },
        { "馬鹿のエリス", 30000, 108, PlayerRaceType::HUMAN },
        { "腹ペコのフィルバート", 30000, 107, PlayerRaceType::VAMPIRE },
        { "スナーグル・サシグア", 30000, 107, PlayerRaceType::MIND_FLAYER },
        { "長死きエロワーズ", 30000, 108, PlayerRaceType::SPECTRE },
        { "ノロマのフンディ", 30000, 108, PlayerRaceType::ZOMBIE },
        { "グランサス", 30000, 107, PlayerRaceType::SKELETON },
        { "丁寧なロラックス", 30000, 107, PlayerRaceType::VAMPIRE },
        { "ブッチ", 30000, 108, PlayerRaceType::HALF_ORC },
        { "美しきエルベレス", 30000, 108, PlayerRaceType::HIGH_ELF },
        { "こそこそサーレス", 30000, 107, PlayerRaceType::GNOME },
        { "ナーロック", 30000, 107, PlayerRaceType::DWARF },
        { "チビのヘイネッカ", 30000, 108, PlayerRaceType::GNOME },
        { "きちがいロワラン", 30000, 108, PlayerRaceType::HALF_GIANT },
        { "毒息のウート", 30000, 107, PlayerRaceType::DRACONIAN },
        { "でぶっちょアラァカ", 30000, 107, PlayerRaceType::DRACONIAN },
        { "低能なプーゴー", 30000, 108, PlayerRaceType::BEASTMAN },
        { "フェロールフィリアン", 30000, 108, PlayerRaceType::ELF },
        { "年寄りマロカ", 30000, 107, PlayerRaceType::GNOME },
        { "勇敢なサシン", 30000, 107, PlayerRaceType::HALF_GIANT },
        { "田舎者アビエマール", 30000, 108, PlayerRaceType::HUMAN },
        { "貧乏なハーク", 30000, 108, PlayerRaceType::HALF_ORC },
        { "みじめなソアリン", 30000, 107, PlayerRaceType::ZOMBIE },
        { "質素なメルラ", 30000, 107, PlayerRaceType::ELF },
#else
        { "Bilbo the Friendly", 30000, 108, PlayerRaceType::HOBBIT },
        { "Rincewind the Chicken", 30000, 108, PlayerRaceType::HUMAN },
        { "Sultan the Midget", 30000, 107, PlayerRaceType::GNOME },
        { "Lyar-el the Comely", 30000, 107, PlayerRaceType::ELF },
        { "Falilmawen the Friendly", 30000, 108, PlayerRaceType::HOBBIT },
        { "Voirin the Cowardly", 30000, 108, PlayerRaceType::HUMAN },
        { "Erashnak the Midget", 30000, 107, PlayerRaceType::BEASTMAN },
        { "Grug the Comely", 30000, 107, PlayerRaceType::HALF_TITAN },
        { "Forovir the Cheap", 30000, 108, PlayerRaceType::HUMAN },
        { "Ellis the Fool", 30000, 108, PlayerRaceType::HUMAN },
        { "Filbert the Hungry", 30000, 107, PlayerRaceType::VAMPIRE },
        { "Fthnargl Psathiggua", 30000, 107, PlayerRaceType::MIND_FLAYER },
        { "Eloise Long-Dead", 30000, 108, PlayerRaceType::SPECTRE },
        { "Fundi the Slow", 30000, 108, PlayerRaceType::ZOMBIE },
        { "Granthus", 30000, 107, PlayerRaceType::SKELETON },
        { "Lorax the Suave", 30000, 107, PlayerRaceType::VAMPIRE },
        { "Butch", 30000, 108, PlayerRaceType::HALF_ORC },
        { "Elbereth the Beautiful", 30000, 108, PlayerRaceType::HIGH_ELF },
        { "Sarleth the Sneaky", 30000, 107, PlayerRaceType::GNOME },
        { "Narlock", 30000, 107, PlayerRaceType::DWARF },
        { "Haneka the Small", 30000, 108, PlayerRaceType::GNOME },
        { "Loirin the Mad", 30000, 108, PlayerRaceType::HALF_GIANT },
        { "Wuto Poisonbreath", 30000, 107, PlayerRaceType::DRACONIAN },
        { "Araaka the Rotund", 30000, 107, PlayerRaceType::DRACONIAN },
        { "Poogor the Dumb", 30000, 108, PlayerRaceType::BEASTMAN },
        { "Felorfiliand", 30000, 108, PlayerRaceType::ELF },
        { "Maroka the Aged", 30000, 107, PlayerRaceType::GNOME },
        { "Sasin the Bold", 30000, 107, PlayerRaceType::HALF_GIANT },
        { "Abiemar the Peasant", 30000, 108, PlayerRaceType::HUMAN },
        { "Hurk the Poor", 30000, 108, PlayerRaceType::HALF_ORC },
        { "Soalin the Wretched", 30000, 107, PlayerRaceType::ZOMBIE },
        { "Merulla the Humble", 30000, 107, PlayerRaceType::ELF },
#endif
    },
    {
/* Armoury - 28 unique names */
#ifdef JP
        { "醜悪コン=ダー", 30000, 115, PlayerRaceType::HALF_ORC },
        { "頑固者ダーグ=ロウ", 30000, 111, PlayerRaceType::HUMAN },
        { "賢者デカド", 30000, 112, PlayerRaceType::DUNADAN },
        { "鍛冶屋のウィーランド", 30000, 112, PlayerRaceType::DWARF },
        { "醜悪コン=ダー", 30000, 115, PlayerRaceType::HALF_ORC },
        { "頑固者ダーグ=ロウ", 30000, 111, PlayerRaceType::HUMAN },
        { "ハンサムなデカド", 30000, 112, PlayerRaceType::AMBERITE },
        { "エロー・ドラゴンスケイル", 30000, 112, PlayerRaceType::ELF },
        { "デリカトス", 30000, 115, PlayerRaceType::SPRITE },
        { "巨大なグルース", 30000, 111, PlayerRaceType::HALF_GIANT },
        { "アニムス", 30000, 112, PlayerRaceType::GOLEM },
        { "マルヴァス", 30000, 112, PlayerRaceType::HALF_TITAN },
        { "セラクシス", 30000, 115, PlayerRaceType::ZOMBIE },
        { "デス・チル", 30000, 111, PlayerRaceType::SPECTRE },
        { "微かなドリオス", 30000, 112, PlayerRaceType::SPECTRE },
        { "冷たいバスリック", 30000, 112, PlayerRaceType::VAMPIRE },
        { "冷酷ヴェンジェラ", 30000, 115, PlayerRaceType::HALF_TROLL },
        { "強者ウィラナ", 30000, 111, PlayerRaceType::HUMAN },
        { "ヨジョ二世", 30000, 112, PlayerRaceType::DWARF },
        { "優しいラナラー", 30000, 112, PlayerRaceType::AMBERITE },
        { "不浄のホルバグ", 30000, 115, PlayerRaceType::HALF_ORC },
        { "テレパスのエレレン", 30000, 111, PlayerRaceType::DARK_ELF },
        { "イスドリリアス", 30000, 112, PlayerRaceType::SPRITE },
        { "一つ目ヴェグナー", 30000, 112, PlayerRaceType::CYCLOPS },
        { "混沌のロディッシュ", 30000, 115, PlayerRaceType::BEASTMAN },
        { "剣豪ヘジン", 30000, 111, PlayerRaceType::NIBELUNG },
        { "ずる屋のエルベレリス", 30000, 112, PlayerRaceType::DARK_ELF },
        { "インプのザサス", 30000, 112, PlayerRaceType::IMP },
        { "醜悪コン=ダー", 30000, 115, PlayerRaceType::HALF_ORC },
        { "頑固者ダーグ=ロウ", 30000, 111, PlayerRaceType::HUMAN },
        { "ハンサムなデカド", 30000, 112, PlayerRaceType::AMBERITE },
        { "鍛冶屋のウィーランド", 30000, 112, PlayerRaceType::DWARF },
#else
        { "Kon-Dar the Ugly", 30000, 115, PlayerRaceType::HALF_ORC },
        { "Darg-Low the Grim", 30000, 111, PlayerRaceType::HUMAN },
        { "Decado the Handsome", 30000, 112, PlayerRaceType::DUNADAN },
        { "Wieland the Smith", 30000, 112, PlayerRaceType::DWARF },
        { "Kon-Dar the Ugly", 30000, 115, PlayerRaceType::HALF_ORC },
        { "Darg-Low the Grim", 30000, 111, PlayerRaceType::HUMAN },
        { "Decado the Handsome", 30000, 112, PlayerRaceType::AMBERITE },
        { "Elo Dragonscale", 30000, 112, PlayerRaceType::ELF },
        { "Delicatus", 30000, 115, PlayerRaceType::SPRITE },
        { "Gruce the Huge", 30000, 111, PlayerRaceType::HALF_GIANT },
        { "Animus", 30000, 112, PlayerRaceType::GOLEM },
        { "Malvus", 30000, 112, PlayerRaceType::HALF_TITAN },
        { "Selaxis", 30000, 115, PlayerRaceType::ZOMBIE },
        { "Deathchill", 30000, 111, PlayerRaceType::SPECTRE },
        { "Drios the Faint", 30000, 112, PlayerRaceType::SPECTRE },
        { "Bathric the Cold", 30000, 112, PlayerRaceType::VAMPIRE },
        { "Vengella the Cruel", 30000, 115, PlayerRaceType::HALF_TROLL },
        { "Wyrana the Mighty", 30000, 111, PlayerRaceType::HUMAN },
        { "Yojo II", 30000, 112, PlayerRaceType::DWARF },
        { "Ranalar the Sweet", 30000, 112, PlayerRaceType::AMBERITE },
        { "Horbag the Unclean", 30000, 115, PlayerRaceType::HALF_ORC },
        { "Elelen the Telepath", 30000, 111, PlayerRaceType::DARK_ELF },
        { "Isedrelias", 30000, 112, PlayerRaceType::SPRITE },
        { "Vegnar One-eye", 30000, 112, PlayerRaceType::CYCLOPS },
        { "Rodish the Chaotic", 30000, 115, PlayerRaceType::BEASTMAN },
        { "Hesin Swordmaster", 30000, 111, PlayerRaceType::NIBELUNG },
        { "Elvererith the Cheat", 30000, 112, PlayerRaceType::DARK_ELF },
        { "Zzathath the Imp", 30000, 112, PlayerRaceType::IMP },
        { "Kon-Dar the Ugly", 30000, 115, PlayerRaceType::HALF_ORC },
        { "Darg-Low the Grim", 30000, 111, PlayerRaceType::HUMAN },
        { "Decado the Handsome", 30000, 112, PlayerRaceType::AMBERITE },
        { "Wieland the Smith", 30000, 112, PlayerRaceType::DWARF },
#endif
    },

    {
/* Weapon Smith - 28 unique names */
#ifdef JP
        { "残忍なるアーノルド", 30000, 115, PlayerRaceType::HALF_TROLL },
        { "獣殺しのアーンダル", 30000, 110, PlayerRaceType::HALF_ELF },
        { "獣マスターのエディー", 30000, 115, PlayerRaceType::HOBBIT },
        { "竜殺しのオグライン", 30000, 112, PlayerRaceType::DWARF },
        { "熟練者ドリュー", 30000, 115, PlayerRaceType::HUMAN },
        { "龍の子オラックス", 30000, 110, PlayerRaceType::DRACONIAN },
        { "病気持ちのアンスラックス", 30000, 115, PlayerRaceType::BEASTMAN },
        { "頑丈者アルコス", 30000, 112, PlayerRaceType::DWARF },
        { "腐れ者のサリアス", 30000, 115, PlayerRaceType::ZOMBIE },
        { "晒し骨のトゥエシク", 30000, 110, PlayerRaceType::SKELETON },
        { "ビリオス", 30000, 115, PlayerRaceType::BEASTMAN },
        { "ファスガル", 30000, 112, PlayerRaceType::ZOMBIE },
        { "パラディンのエレフリス", 30000, 115, PlayerRaceType::BARBARIAN },
        { "キ'トリッ'ク", 30000, 110, PlayerRaceType::KLACKON },
        { "蜘蛛の友ドゥロカス", 30000, 115, PlayerRaceType::DARK_ELF },
        { "巨人殺しのフングス", 30000, 112, PlayerRaceType::DWARF },
        { "デランサ", 30000, 115, PlayerRaceType::ELF },
        { "レンジャーのソルビスタニ", 30000, 110, PlayerRaceType::HALF_ELF },
        { "ノロマのゾリル", 30000, 115, PlayerRaceType::GOLEM },
        { "イーオン・フラックス", 30000, 112, PlayerRaceType::HALF_ELF },
        { "強者ナドック", 30000, 115, PlayerRaceType::HOBBIT },
        { "弱虫エラモグ", 30000, 110, PlayerRaceType::KOBOLD },
        { "公正なエオウィリス", 30000, 115, PlayerRaceType::VAMPIRE },
        { "バルログ殺しのヒュイモグ", 30000, 112, PlayerRaceType::HALF_ORC },
        { "冷酷ピーダス", 30000, 115, PlayerRaceType::HUMAN },
        { "ヴァモグ スレイヤー", 30000, 110, PlayerRaceType::HALF_OGRE },
        { "性悪フーシュナク", 30000, 115, PlayerRaceType::BEASTMAN },
        { "舞闘バレン", 30000, 112, PlayerRaceType::BARBARIAN },
        { "残忍なるアーノルド", 30000, 115, PlayerRaceType::BARBARIAN },
        { "獣殺しのアーンダル", 30000, 110, PlayerRaceType::HALF_ELF },
        { "ビーストマスター・エディー", 30000, 115, PlayerRaceType::HALF_ORC },
        { "竜殺しのオグライン", 30000, 112, PlayerRaceType::DWARF },
#else
        { "Arnold the Beastly", 30000, 115, PlayerRaceType::BARBARIAN },
        { "Arndal Beast-Slayer", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Eddie Beast-Master", 30000, 115, PlayerRaceType::HALF_ORC },
        { "Oglign Dragon-Slayer", 30000, 112, PlayerRaceType::DWARF },
        { "Drew the Skilled", 30000, 115, PlayerRaceType::HUMAN },
        { "Orrax Dragonson", 30000, 110, PlayerRaceType::DRACONIAN },
        { "Anthrax Disease-Carrier", 30000, 115, PlayerRaceType::BEASTMAN },
        { "Arkhoth the Stout", 30000, 112, PlayerRaceType::DWARF },
        { "Sarlyas the Rotten", 30000, 115, PlayerRaceType::ZOMBIE },
        { "Tuethic Bare-Bones", 30000, 110, PlayerRaceType::SKELETON },
        { "Bilious", 30000, 115, PlayerRaceType::BEASTMAN },
        { "Fasgul", 30000, 112, PlayerRaceType::ZOMBIE },
        { "Ellefris the Paladin", 30000, 115, PlayerRaceType::BARBARIAN },
        { "K'trrik'k", 30000, 110, PlayerRaceType::KLACKON },
        { "Drocus Spiderfriend", 30000, 115, PlayerRaceType::DARK_ELF },
        { "Fungus Giant-Slayer", 30000, 112, PlayerRaceType::DWARF },
        { "Delantha", 30000, 115, PlayerRaceType::ELF },
        { "Solvistani the Ranger", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Xoril the Slow", 30000, 115, PlayerRaceType::GOLEM },
        { "Aeon Flux", 30000, 112, PlayerRaceType::HALF_ELF },
        { "Nadoc the Strong", 30000, 115, PlayerRaceType::HOBBIT },
        { "Eramog the Weak", 30000, 110, PlayerRaceType::KOBOLD },
        { "Eowilith the Fair", 30000, 115, PlayerRaceType::VAMPIRE },
        { "Huimog Balrog-Slayer", 30000, 112, PlayerRaceType::HALF_ORC },
        { "Peadus the Cruel", 30000, 115, PlayerRaceType::HUMAN },
        { "Vamog Slayer", 30000, 110, PlayerRaceType::HALF_OGRE },
        { "Hooshnak the Vicious", 30000, 115, PlayerRaceType::BEASTMAN },
        { "Balenn War-Dancer", 30000, 112, PlayerRaceType::BARBARIAN },
        { "Arnold the Beastly", 30000, 115, PlayerRaceType::BARBARIAN },
        { "Arndal Beast-Slayer", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Eddie Beast-Master", 30000, 115, PlayerRaceType::HALF_ORC },
        { "Oglign Dragon-Slayer", 30000, 112, PlayerRaceType::DWARF },
#endif
    },
    {
/* Temple - 22 unique names */
#ifdef JP
        { "質素なルードヴィヒ", 30000, 109, PlayerRaceType::HUMAN },
        { "パラディンのガンナー", 30000, 110, PlayerRaceType::HUMAN },
        { "選ばれしトリン", 30000, 107, PlayerRaceType::ELF },
        { "賢明なるサラストロ", 30000, 109, PlayerRaceType::DWARF },
        { "パーシヴァル卿", 30000, 107, PlayerRaceType::HIGH_ELF },
        { "神聖なるアセナス", 30000, 109, PlayerRaceType::HUMAN },
        { "マッキノン", 30000, 109, PlayerRaceType::HUMAN },
        { "謹み婦人", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "ドルイドのハシュニック", 30000, 107, PlayerRaceType::HOBBIT },
        { "フィナク", 30000, 109, PlayerRaceType::YEEK },
        { "クリキック", 30000, 109, PlayerRaceType::KLACKON },
        { "荒くれ者モリヴァル", 30000, 110, PlayerRaceType::ELF },
        { "暗きホシャック", 30000, 107, PlayerRaceType::IMP },
        { "賢者アタール", 30000, 109, PlayerRaceType::HUMAN },
        { "清きイベニッド", 30000, 109, PlayerRaceType::HUMAN },
        { "エリディシュ", 30000, 110, PlayerRaceType::HALF_TROLL },
        { "呪術師ヴルドゥシュ", 30000, 107, PlayerRaceType::HALF_OGRE },
        { "狂戦士ハオブ", 30000, 109, PlayerRaceType::BARBARIAN },
        { "若きプルーグディシュ", 30000, 109, PlayerRaceType::HALF_OGRE },
        { "きちがいラムワイズ", 30000, 110, PlayerRaceType::YEEK },
        { "有徳者ムワート", 30000, 107, PlayerRaceType::KOBOLD },
        { "弱虫ダードバード", 30000, 109, PlayerRaceType::SPECTRE },
        { "質素なルードヴィヒ", 30000, 109, PlayerRaceType::HUMAN },
        { "パラディンのガンナー", 30000, 110, PlayerRaceType::HUMAN },
        { "選ばれしトリン", 30000, 107, PlayerRaceType::ELF },
        { "賢明なるサラストロ", 30000, 109, PlayerRaceType::DWARF },
        { "パーシヴァル卿", 30000, 107, PlayerRaceType::HIGH_ELF },
        { "神聖なるアセナス", 30000, 109, PlayerRaceType::HUMAN },
        { "マッキノン", 30000, 109, PlayerRaceType::HUMAN },
        { "謹み婦人", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "ドルイドのハシュニック", 30000, 107, PlayerRaceType::HOBBIT },
        { "フィナク", 30000, 109, PlayerRaceType::YEEK },
#else
        { "Ludwig the Humble", 30000, 109, PlayerRaceType::DWARF },
        { "Gunnar the Paladin", 30000, 110, PlayerRaceType::HALF_TROLL },
        { "Torin the Chosen", 30000, 107, PlayerRaceType::HIGH_ELF },
        { "Sarastro the Wise", 30000, 109, PlayerRaceType::HUMAN },
        { "Sir Parsival the Pure", 30000, 107, PlayerRaceType::HIGH_ELF },
        { "Asenath the Holy", 30000, 109, PlayerRaceType::HUMAN },
        { "McKinnon", 30000, 109, PlayerRaceType::HUMAN },
        { "Mistress Chastity", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "Hashnik the Druid", 30000, 107, PlayerRaceType::HOBBIT },
        { "Finak", 30000, 109, PlayerRaceType::YEEK },
        { "Krikkik", 30000, 109, PlayerRaceType::KLACKON },
        { "Morival the Wild", 30000, 110, PlayerRaceType::ELF },
        { "Hoshak the Dark", 30000, 107, PlayerRaceType::IMP },
        { "Atal the Wise", 30000, 109, PlayerRaceType::HUMAN },
        { "Ibenidd the Chaste", 30000, 109, PlayerRaceType::HUMAN },
        { "Eridish", 30000, 110, PlayerRaceType::HALF_TROLL },
        { "Vrudush the Shaman", 30000, 107, PlayerRaceType::HALF_OGRE },
        { "Haob the Berserker", 30000, 109, PlayerRaceType::BARBARIAN },
        { "Proogdish the Youthfull", 30000, 109, PlayerRaceType::HALF_OGRE },
        { "Lumwise the Mad", 30000, 110, PlayerRaceType::YEEK },
        { "Muirt the Virtuous", 30000, 107, PlayerRaceType::KOBOLD },
        { "Dardobard the Weak", 30000, 109, PlayerRaceType::SPECTRE },
        { "Ludwig the Humble", 30000, 109, PlayerRaceType::DWARF },
        { "Gunnar the Paladin", 30000, 110, PlayerRaceType::HALF_TROLL },
        { "Torin the Chosen", 30000, 107, PlayerRaceType::HIGH_ELF },
        { "Sarastro the Wise", 30000, 109, PlayerRaceType::HUMAN },
        { "Sir Parsival the Pure", 30000, 107, PlayerRaceType::HIGH_ELF },
        { "Asenath the Holy", 30000, 109, PlayerRaceType::HUMAN },
        { "McKinnon", 30000, 109, PlayerRaceType::HUMAN },
        { "Mistress Chastity", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "Hashnik the Druid", 30000, 107, PlayerRaceType::HOBBIT },
        { "Finak", 30000, 109, PlayerRaceType::YEEK },
#endif
    },
    {
/* Alchemist - 26 unique names */
#ifdef JP
        { "化学者マウザー", 30000, 111, PlayerRaceType::HALF_ELF },
        { "カオスのウィズル", 30000, 110, PlayerRaceType::HOBBIT },
        { "強欲ミダス", 30000, 116, PlayerRaceType::GNOME },
        { "貧弱ジャ=ファー", 30000, 111, PlayerRaceType::ELF }, /*FIRST*/
        { "カカルラカカル", 30000, 116, PlayerRaceType::KLACKON },
        { "錬金術師ジャル=エス", 30000, 111, PlayerRaceType::ELF },
        { "用心深いファネラス", 30000, 111, PlayerRaceType::DWARF },
        { "キチガイのルンシー", 30000, 110, PlayerRaceType::HUMAN },
        { "グランブルワース", 30000, 116, PlayerRaceType::GNOME },
        { "フリッター", 30000, 111, PlayerRaceType::SPRITE },
        { "ザリルス", 30000, 111, PlayerRaceType::HUMAN },
        { "古きエグバート", 30000, 110, PlayerRaceType::DWARF },
        { "誇り高きヴァリンドラ", 30000, 116, PlayerRaceType::HIGH_ELF },
        { "錬金術師タエン", 30000, 111, PlayerRaceType::HUMAN },
        { "巧言カイド", 30000, 111, PlayerRaceType::VAMPIRE },
        { "暗きフリア", 30000, 110, PlayerRaceType::NIBELUNG },
        { "質素なドムリ", 30000, 116, PlayerRaceType::DWARF },
        { "魔の子ヤァジュッカ", 30000, 111, PlayerRaceType::IMP },
        { "薬草師ジェララルドール", 30000, 111, PlayerRaceType::HIGH_ELF },
        { "賢者オレラルダン", 30000, 110, PlayerRaceType::BARBARIAN },
        { "デモニシストのフゾグロ", 30000, 116, PlayerRaceType::IMP },
        { "錬金術師ドゥリアシュ", 30000, 111, PlayerRaceType::HALF_ORC },
        { "強者ネリア", 30000, 111, PlayerRaceType::CYCLOPS },
        { "辛口リグナス", 30000, 110, PlayerRaceType::HALF_ORC },
        { "ティルバ", 30000, 116, PlayerRaceType::HOBBIT },
        { "金持ちミリルドリック", 30000, 111, PlayerRaceType::HUMAN },

        { "科学者マウザー", 30000, 111, PlayerRaceType::HALF_ELF },
        { "カオスのウィズル", 30000, 110, PlayerRaceType::HOBBIT },
        { "強欲ミダス", 30000, 116, PlayerRaceType::GNOME },
        { "錬金術師ジャ=ファー", 30000, 111, PlayerRaceType::ELF },
        { "カカルラカカル", 30000, 116, PlayerRaceType::KLACKON },
        { "錬金術師ジャル=エス", 30000, 111, PlayerRaceType::ELF },
#else
        { "Mauser the Chemist", 30000, 111, PlayerRaceType::HALF_ELF },
        { "Wizzle the Chaotic", 30000, 110, PlayerRaceType::HOBBIT },
        { "Midas the Greedy", 30000, 116, PlayerRaceType::GNOME },
        { "Ja-Far the Alchemist", 30000, 111, PlayerRaceType::ELF },
        { "Kakalrakakal", 30000, 116, PlayerRaceType::KLACKON },
        { "Jal-Eth the Alchemist", 30000, 111, PlayerRaceType::ELF },
        { "Fanelath the Cautious", 30000, 111, PlayerRaceType::DWARF },
        { "Runcie the Insane", 30000, 110, PlayerRaceType::HUMAN },
        { "Grumbleworth", 30000, 116, PlayerRaceType::GNOME },
        { "Flitter", 30000, 111, PlayerRaceType::SPRITE },
        { "Xarillus", 30000, 111, PlayerRaceType::HUMAN },
        { "Egbert the Old", 30000, 110, PlayerRaceType::DWARF },
        { "Valindra the Proud", 30000, 116, PlayerRaceType::HIGH_ELF },
        { "Taen the Alchemist", 30000, 111, PlayerRaceType::HUMAN },
        { "Cayd the Sweet", 30000, 111, PlayerRaceType::VAMPIRE },
        { "Fulir the Dark", 30000, 110, PlayerRaceType::NIBELUNG },
        { "Domli the Humble", 30000, 116, PlayerRaceType::DWARF },
        { "Yaarjukka Demonspawn", 30000, 111, PlayerRaceType::IMP },
        { "Gelaraldor the Herbmaster", 30000, 111, PlayerRaceType::HIGH_ELF },
        { "Olelaldan the Wise", 30000, 110, PlayerRaceType::BARBARIAN },
        { "Fthoglo the Demonicist", 30000, 116, PlayerRaceType::IMP },
        { "Dridash the Alchemist", 30000, 111, PlayerRaceType::HALF_ORC },
        { "Nelir the Strong", 30000, 111, PlayerRaceType::CYCLOPS },
        { "Lignus the Pungent", 30000, 110, PlayerRaceType::HALF_ORC },
        { "Tilba", 30000, 116, PlayerRaceType::HOBBIT },
        { "Myrildric the Wealthy", 30000, 111, PlayerRaceType::HUMAN },

        { "Mauser the Chemist", 30000, 111, PlayerRaceType::HALF_ELF },
        { "Wizzle the Chaotic", 30000, 110, PlayerRaceType::HOBBIT },
        { "Midas the Greedy", 30000, 116, PlayerRaceType::GNOME },
        { "Ja-Far the Alchemist", 30000, 111, PlayerRaceType::ELF },
        { "Kakalrakakal", 30000, 116, PlayerRaceType::KLACKON },
        { "Jal-Eth the Alchemist", 30000, 111, PlayerRaceType::ELF },
#endif
    },

    {
/* Magic Shop - 23 unique names */
#ifdef JP
        { "ソーサラーのロ=パン", 30000, 110, PlayerRaceType::HALF_ELF },
        { "偉大なるブガービイ", 30000, 113, PlayerRaceType::GNOME },
        { "イェンダーの魔法使い", 30000, 110, PlayerRaceType::HUMAN },
        { "死霊使いリャク", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "魔術師スキドゥニー", 30000, 110, PlayerRaceType::HALF_ELF },
        { "幻術師キリア", 30000, 110, PlayerRaceType::HUMAN },
        { "死霊術師ニッキ", 30000, 110, PlayerRaceType::DARK_ELF },
        { "ソロストラン", 30000, 110, PlayerRaceType::SPRITE },
        { "烏賊口アチシェ", 30000, 113, PlayerRaceType::MIND_FLAYER },
        { "貴族のカザ", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "暗きファジル", 30000, 110, PlayerRaceType::DARK_ELF },
        { "偉大なるケルドーン", 30000, 110, PlayerRaceType::DWARF },
        { "フィランスロプス", 30000, 113, PlayerRaceType::HOBBIT },
        { "魔女のアグナー", 30000, 110, PlayerRaceType::HUMAN },
        { "死霊術師ビュリアンス", 30000, 110, PlayerRaceType::BEASTMAN },
        { "ハイメイジのヴイラク", 30000, 110, PlayerRaceType::BEASTMAN },
        { "知恵者マディッシュ", 30000, 113, PlayerRaceType::BEASTMAN },
        { "ファレブリンボール", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "陰険フェリル=ガンド", 30000, 110, PlayerRaceType::DARK_ELF },
        { "呪術師サレゴード", 30000, 110, PlayerRaceType::BARBARIAN },
        { "神秘家クトゥアロス", 30000, 113, PlayerRaceType::MIND_FLAYER },
        { "幻術師イベリ", 30000, 110, PlayerRaceType::SKELETON },
        { "死霊術師ヘトー", 30000, 110, PlayerRaceType::YEEK },
        { "魔術師ロ=パン", 30000, 110, PlayerRaceType::HALF_ELF },
        { "偉大なるブガービイ", 30000, 113, PlayerRaceType::GNOME },
        { "イェンダーの魔法使い", 30000, 110, PlayerRaceType::HUMAN },
        { "死霊術師リャク", 30000, 110, PlayerRaceType::DARK_ELF },
        { "魔術師スキドゥニー", 30000, 110, PlayerRaceType::HALF_ELF },
        { "幻術師キリア", 30000, 110, PlayerRaceType::HUMAN },
        { "死霊術師ニッキ", 30000, 110, PlayerRaceType::DARK_ELF },
        { "ソロストラン", 30000, 110, PlayerRaceType::SPRITE },
        { "烏賊口アチシェ", 30000, 113, PlayerRaceType::MIND_FLAYER },
#else
        { "Lo Pan the Sorcerer", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Buggerby the Great", 30000, 113, PlayerRaceType::GNOME },
        { "The Wizard of Yendor", 30000, 110, PlayerRaceType::HUMAN },
        { "Rjak the Necromancer", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Skidney the Sorcerer", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Kyria the Illusionist", 30000, 110, PlayerRaceType::HUMAN },
        { "Nikki the Necromancer", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Solostoran", 30000, 110, PlayerRaceType::SPRITE },
        { "Achshe the Tentacled", 30000, 113, PlayerRaceType::MIND_FLAYER },
        { "Kaza the Noble", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "Fazzil the Dark", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Keldorn the Grand", 30000, 110, PlayerRaceType::DWARF },
        { "Philanthropus", 30000, 113, PlayerRaceType::HOBBIT },
        { "Agnar the Enchantress", 30000, 110, PlayerRaceType::HUMAN },
        { "Buliance the Necromancer", 30000, 110, PlayerRaceType::BEASTMAN },
        { "Vuirak the High-Mage", 30000, 110, PlayerRaceType::BEASTMAN },
        { "Madish the Smart", 30000, 113, PlayerRaceType::BEASTMAN },
        { "Falebrimbor", 30000, 110, PlayerRaceType::HIGH_ELF },
        { "Felil-Gand the Subtle", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Thalegord the Shaman", 30000, 110, PlayerRaceType::BARBARIAN },
        { "Cthoaloth the Mystic", 30000, 113, PlayerRaceType::MIND_FLAYER },
        { "Ibeli the Illusionist", 30000, 110, PlayerRaceType::SKELETON },
        { "Heto the Necromancer", 30000, 110, PlayerRaceType::YEEK },
        { "Lo Pan the Sorcerer", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Buggerby the Great", 30000, 113, PlayerRaceType::GNOME },
        { "The Wizard of Yendor", 30000, 110, PlayerRaceType::HUMAN },
        { "Rjak the Necromancer", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Skidney the Sorcerer", 30000, 110, PlayerRaceType::HALF_ELF },
        { "Kyria the Illusionist", 30000, 110, PlayerRaceType::HUMAN },
        { "Nikki the Necromancer", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Solostoran", 30000, 110, PlayerRaceType::SPRITE },
        { "Achshe the Tentacled", 30000, 113, PlayerRaceType::MIND_FLAYER },
#endif
    },
    {
/* Black Market - 32 unique names */
#ifdef JP
        { "ガリー=ギガズ", 60000, 150, PlayerRaceType::HALF_TROLL },
        { "ゴブリンのヒストーア", 60000, 150, PlayerRaceType::HALF_ORC },
        { "フェレンギ人クアーク", 60000, 150, PlayerRaceType::HUMAN },
        { "公正なる(?)トッピ", 60000, 150, PlayerRaceType::ELF },
        { "死人ヴァッサ", 60000, 150, PlayerRaceType::ZOMBIE },
        { "裏切り者カイン", 60000, 150, PlayerRaceType::VAMPIRE },
        { "ブボニカス", 60000, 150, PlayerRaceType::BEASTMAN },
        { "コープスライト", 60000, 150, PlayerRaceType::SPECTRE },
        { "血に飢えしパリッシュ", 60000, 150, PlayerRaceType::VAMPIRE },
        { "ヴァイル", 60000, 150, PlayerRaceType::SKELETON },
        { "信頼のプレンティス", 60000, 150, PlayerRaceType::SKELETON },
        { "人間殺しのグリエラ", 60000, 150, PlayerRaceType::IMP },
        { "エンジェル", 60000, 150, PlayerRaceType::VAMPIRE },
        { "水膨れフロツァム", 60000, 150, PlayerRaceType::ZOMBIE },
        { "ニーヴァル", 60000, 150, PlayerRaceType::VAMPIRE },
        { "明るいアナスタシア", 60000, 150, PlayerRaceType::SPECTRE },
        { "死霊術師チャリティー", 60000, 150, PlayerRaceType::DARK_ELF },
        { "ボクサーのプグナシオス", 60000, 150, PlayerRaceType::HALF_ORC },
        { "幸運なフットソア", 60000, 150, PlayerRaceType::BEASTMAN },
        { "光指のシドリア", 60000, 150, PlayerRaceType::HUMAN },
        { "手品師リアソー", 60000, 150, PlayerRaceType::HOBBIT },
        { "やりくり上手のジャナッカ", 60000, 150, PlayerRaceType::GNOME },
        { "悪党シーナ", 60000, 150, PlayerRaceType::GNOME },
        { "大爪アルニッキ", 60000, 150, PlayerRaceType::DRACONIAN },
        { "貧乏チャエアンド", 60000, 150, PlayerRaceType::HUMAN },
        { "山賊アファードーフ", 60000, 150, PlayerRaceType::BARBARIAN },
        { "強欲ラザクスル", 60000, 150, PlayerRaceType::MIND_FLAYER },
        { "ファラレウィン", 60000, 150, PlayerRaceType::SPRITE },
        { "しわしわヴォスール", 60000, 150, PlayerRaceType::NIBELUNG },
        { "ハンサムなアラオード", 60000, 150, PlayerRaceType::AMBERITE },
        { "負け犬セラドフリド", 60000, 150, PlayerRaceType::HUMAN },
        { "片足のエルーロ", 60000, 150, PlayerRaceType::HALF_OGRE },
#else
        { "Gary Gygaz", 60000, 150, PlayerRaceType::HALF_TROLL },
        { "Histor the Goblin", 60000, 150, PlayerRaceType::HALF_ORC },
        { "Quark the Ferengi", 60000, 150, PlayerRaceType::DWARF },
        { "Topi the Fair(?)", 60000, 150, PlayerRaceType::HUMAN },
        { "Vhassa the Dead", 60000, 150, PlayerRaceType::ZOMBIE },
        { "Kyn the Treacherous", 60000, 150, PlayerRaceType::VAMPIRE },
        { "Bubonicus", 60000, 150, PlayerRaceType::BEASTMAN },
        { "Corpselight", 60000, 150, PlayerRaceType::SPECTRE },
        { "Parrish the Bloodthirsty", 60000, 150, PlayerRaceType::VAMPIRE },
        { "Vile", 60000, 150, PlayerRaceType::SKELETON },
        { "Prentice the Trusted", 60000, 150, PlayerRaceType::SKELETON },
        { "Griella Humanslayer", 60000, 150, PlayerRaceType::IMP },
        { "Angel", 60000, 150, PlayerRaceType::VAMPIRE },
        { "Flotsam the Bloated", 60000, 150, PlayerRaceType::ZOMBIE },
        { "Nieval", 60000, 150, PlayerRaceType::VAMPIRE },
        { "Anastasia the Luminous", 60000, 150, PlayerRaceType::SPECTRE },
        { "Charity the Necromancer", 60000, 150, PlayerRaceType::DARK_ELF },
        { "Pugnacious the Pugilist", 60000, 150, PlayerRaceType::HALF_ORC },
        { "Footsore the Lucky", 60000, 150, PlayerRaceType::BEASTMAN },
        { "Sidria Lighfingered", 60000, 150, PlayerRaceType::HUMAN },
        { "Riatho the Juggler", 60000, 150, PlayerRaceType::HOBBIT },
        { "Janaaka the Shifty", 60000, 150, PlayerRaceType::GNOME },
        { "Cina the Rogue", 60000, 150, PlayerRaceType::GNOME },
        { "Arunikki Greatclaw", 60000, 150, PlayerRaceType::DRACONIAN },
        { "Chaeand the Poor", 60000, 150, PlayerRaceType::HUMAN },
        { "Afardorf the Brigand", 60000, 150, PlayerRaceType::BARBARIAN },
        { "Lathaxl the Greedy", 60000, 150, PlayerRaceType::MIND_FLAYER },
        { "Falarewyn", 60000, 150, PlayerRaceType::SPRITE },
        { "Vosur the Wrinkled", 60000, 150, PlayerRaceType::NIBELUNG },
        { "Araord the Handsome", 60000, 150, PlayerRaceType::AMBERITE },
        { "Theradfrid the Loser", 60000, 150, PlayerRaceType::HUMAN },
        { "One-Legged Eroolo", 60000, 150, PlayerRaceType::HALF_OGRE },
#endif
    },
    {
        /* Home */
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
        { _("我が家", "Your home"), 0, 100, PlayerRaceType::HUMAN },
    },

    {
/* Bookstore - 21 unique names */
#ifdef JP
        { "強欲ドラフ", 30000, 108, PlayerRaceType::HUMAN },
        { "賢者オドナー", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "中立のガンダー", 30000, 110, PlayerRaceType::DARK_ELF },
        { "忍耐の人ロ=シャ", 30000, 105, PlayerRaceType::ELF },
        { "ランドルフ・カーター", 30000, 108, PlayerRaceType::HUMAN },
        { "隼のサライ", 30000, 108, PlayerRaceType::HUMAN },
        { "千里眼ボドリル", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "沈黙のヴェオロイン", 30000, 110, PlayerRaceType::ZOMBIE },
        { "学者のヴァンシラス", 30000, 105, PlayerRaceType::MIND_FLAYER },
        { "物書きオセイン", 30000, 108, PlayerRaceType::SKELETON },
        { "本の虫オルヴァー", 30000, 105, PlayerRaceType::VAMPIRE },
        { "浅井墓男", 30000, 110, PlayerRaceType::ZOMBIE },
        { "デスマスク", 30000, 105, PlayerRaceType::ZOMBIE },
        { "学者のアスーヌ", 30000, 108, PlayerRaceType::MIND_FLAYER },
        { "死人のプリランド", 30000, 105, PlayerRaceType::ZOMBIE },
        { "鉄のロナール", 30000, 110, PlayerRaceType::GOLEM },
#else
        { "Dolaf the Greedy", 30000, 108, PlayerRaceType::HUMAN },
        { "Odnar the Sage", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "Gandar the Neutral", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Ro-sha the Patient", 30000, 105, PlayerRaceType::ELF },
        { "Randolph Carter", 30000, 108, PlayerRaceType::HUMAN },
        { "Sarai the Swift", 30000, 108, PlayerRaceType::HUMAN },
        { "Bodril the Seer", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "Veloin the Quiet", 30000, 110, PlayerRaceType::ZOMBIE },
        { "Vanthylas the Learned", 30000, 105, PlayerRaceType::MIND_FLAYER },
        { "Ossein the Literate", 30000, 108, PlayerRaceType::SKELETON },
        { "Olvar Bookworm", 30000, 105, PlayerRaceType::VAMPIRE },
        { "Shallowgrave", 30000, 110, PlayerRaceType::ZOMBIE },
        { "Death Mask", 30000, 105, PlayerRaceType::ZOMBIE },
        { "Asuunu the Learned", 30000, 108, PlayerRaceType::MIND_FLAYER },
        { "Prirand the Dead", 30000, 105, PlayerRaceType::ZOMBIE },
        { "Ronar the Iron", 30000, 110, PlayerRaceType::GOLEM },
#endif
#ifdef JP
        { "ガリル=ガミル", 30000, 105, PlayerRaceType::ELF },
        { "本食いローバグ", 30000, 108, PlayerRaceType::KOBOLD },
        { "キリアリキーク", 30000, 105, PlayerRaceType::KLACKON },
        { "静かなるリリン", 30000, 110, PlayerRaceType::DWARF },
        { "王者イサング", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "強欲ドラフ", 30000, 108, PlayerRaceType::HUMAN },
        { "賢者オドナー", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "中立のガンダー", 30000, 110, PlayerRaceType::DARK_ELF },
        { "忍耐の人ロ=シャ", 30000, 105, PlayerRaceType::ELF },
        { "ランドルフ・カーター", 30000, 108, PlayerRaceType::HUMAN },
        { "隼サライ", 30000, 108, PlayerRaceType::HUMAN },
        { "千里眼ボドリル", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "沈黙のヴェオロイン", 30000, 110, PlayerRaceType::ZOMBIE },
        { "学者のヴァンシラス", 30000, 105, PlayerRaceType::MIND_FLAYER },
        { "物書きオセイン", 30000, 108, PlayerRaceType::SKELETON },
        { "本の虫オルヴァー", 30000, 105, PlayerRaceType::VAMPIRE },
#else
        { "Galil-Gamir", 30000, 105, PlayerRaceType::ELF },
        { "Rorbag Book-Eater", 30000, 108, PlayerRaceType::KOBOLD },
        { "Kiriarikirk", 30000, 105, PlayerRaceType::KLACKON },
        { "Rilin the Quiet", 30000, 110, PlayerRaceType::DWARF },
        { "Isung the Lord", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "Dolaf the Greedy", 30000, 108, PlayerRaceType::HUMAN },
        { "Odnar the Sage", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "Gandar the Neutral", 30000, 110, PlayerRaceType::DARK_ELF },
        { "Ro-sha the Patient", 30000, 105, PlayerRaceType::ELF },
        { "Randolph Carter", 30000, 108, PlayerRaceType::HUMAN },
        { "Sarai the Swift", 30000, 108, PlayerRaceType::HUMAN },
        { "Bodril the Seer", 30000, 105, PlayerRaceType::HIGH_ELF },
        { "Veloin the Quiet", 30000, 110, PlayerRaceType::ZOMBIE },
        { "Vanthylas the Learned", 30000, 105, PlayerRaceType::MIND_FLAYER },
        { "Ossein the Literate", 30000, 108, PlayerRaceType::SKELETON },
        { "Olvar Bookworm", 30000, 105, PlayerRaceType::VAMPIRE },
#endif
    },

    {
        /* Museum */
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
        { _("博物館", "Museum"), 0, 100, PlayerRaceType::HUMAN },
    },
};
