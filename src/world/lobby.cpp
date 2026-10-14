#include "lobby.h"
#include "entities/player.h"
#include "world/lobby.h"


Lobby::Lobby(const sf::RenderWindow& window) {

	// Defines the size of all lobby buildings.
	const sf::Vector2f buildingSize(384.f, 384.f);

	// Defines the distance between shops and window edges.
	const float margin = 20.f;

	// Stores the window dimensions.
	const float windowWidth = static_cast<float>(window.getSize().x);
	const float windowHeight = static_cast<float>(window.getSize().y);

	// Configure the weapon shop area.
	weaponShop.setSize(buildingSize);

	// Load the weapon shop texture.
	if (!weaponShopTexture.loadFromFile("assets/buildings/weaponShop.png")) {
		throw std::runtime_error("Failed to load weapon shop texture");
	}

	weaponShop.setTexture(&weaponShopTexture);

	// Center the origin so positioning is based on the middle of the shape.
	weaponShop.setOrigin({
		static_cast<float>(weaponShop.getLocalBounds().size.x / 2),
		static_cast<float>(weaponShop.getLocalBounds().size.y) / 2
		});

	// Positions the weapon shop near the bottom-left area.
	weaponShop.setPosition({
		windowWidth * 0.25f,
		windowHeight - buildingSize.y / 2.f - margin
		});


	// Configure the armory area.
	armory.setSize(buildingSize);

	// Load the armory texture.
	if (!armoryTexture.loadFromFile("assets/buildings/armory.png")) {
		throw std::runtime_error("Failed to load armory texture");
	}
	armory.setTexture(&armoryTexture);

	armory.setOrigin({
		static_cast<float>(armory.getLocalBounds().size.x / 2),
		static_cast<float>(armory.getLocalBounds().size.y) / 2
		});

	// Positions the armory near the bottom-right area.
	armory.setPosition({
		windowWidth * 0.75f,
		windowHeight - buildingSize.y / 2.f - margin
		});


	// Configure the doctor area.
	doctor.setSize(buildingSize);
	
	// Load the doctor texture.
	if (!doctorTexture.loadFromFile("assets/buildings/doctor.png")) {
		throw std::runtime_error("Failed to load doctor texture");
	}
	doctor.setTexture(&doctorTexture);

	doctor.setOrigin({
		static_cast<float>(doctor.getLocalBounds().size.x / 2),
		static_cast<float>(doctor.getLocalBounds().size.y) / 2
		});

	// Positions the doctor near the right edge.
	doctor.setPosition({
		windowWidth - buildingSize.x / 2.f - margin,
		windowHeight / 2.f
		});


	// Configure the wizard area.
	wizard.setSize(buildingSize);
	
	// Load the wizard texture.
	if (!wizardTexture.loadFromFile("assets/buildings/wizard.png")) {
		throw std::runtime_error("Failed to load wizard texture");
	}
	wizard.setTexture(&wizardTexture);

	wizard.setOrigin({
		static_cast<float>(wizard.getLocalBounds().size.x / 2),
		static_cast<float>(wizard.getLocalBounds().size.y) / 2
		});

	// Positions the wizard near the left edge.
	wizard.setPosition({
		buildingSize.x / 2.f + margin,
		windowHeight / 2.f
		});

	// Configure the cave entrance.
	caveEntrance.setSize(buildingSize);

	// Load the cave entrance texture.
	if (!caveEntranceTexture.loadFromFile("assets/buildings/caveEntrance.png")) {
		throw std::runtime_error("Failed to load cave entrance texture");
	}
	caveEntrance.setTexture(&caveEntranceTexture);

	caveEntrance.setOrigin({
		static_cast<float>(caveEntrance.getLocalBounds().size.x / 2),
		static_cast<float>(caveEntrance.getLocalBounds().size.y) / 2
		});

	// Positions the cave entrance near the top edge.
	caveEntrance.setPosition({
		windowWidth / 2.f,
		buildingSize.y / 2.f + margin
		});
	}

void Lobby::draw(sf::RenderWindow& window) const {

	// Draw the lobby background first.
	window.clear(sf::Color(160, 80, 0));

	// Draw all interactive locations.
	window.draw(weaponShop);
	window.draw(armory);
	window.draw(doctor);
	window.draw(wizard);
	window.draw(caveEntrance);
}


LobbyLocation Lobby::playerLocation(const Player& player) {

	sf::Vector2f playerPosition = player.getPosition();


	// Check whether the player's position is inside
	// one of the lobby interaction rectangles.
	if (weaponShop.getGlobalBounds().contains(playerPosition)) {
		location = LobbyLocation::weaponShop;
	}

	else if (armory.getGlobalBounds().contains(playerPosition)) {
		location = LobbyLocation::armory;
	}

	else if (doctor.getGlobalBounds().contains(playerPosition)) {
		location = LobbyLocation::doctor;
	}

	else if (wizard.getGlobalBounds().contains(playerPosition)) {
		location = LobbyLocation::wizard;
	}

	else if (caveEntrance.getGlobalBounds().contains(playerPosition)) {
		location = LobbyLocation::caveEntrance;
	}

	else {
		location = LobbyLocation::Default;
	}


	return location;
}


std::string Lobby::getName(LobbyLocation location) {

	// Return the text displayed for each interactive lobby area.
	switch (location) {

	case LobbyLocation::weaponShop:
		return "Weapons";

	case LobbyLocation::armory:
		return "Armory";

	case LobbyLocation::doctor:
		return "Doctor";

	case LobbyLocation::wizard:
		return "Wizard";

	case LobbyLocation::caveEntrance:
		return "Cave";

	default:
		return "Default";
	}
}