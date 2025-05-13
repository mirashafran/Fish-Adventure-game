#include "MovingObject.h"

MovingObject::MovingObject(const sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& size, int frameCount, int frameRow, int rowsNum, int maxPhotos) 
	:GameObject(texture, position, size), m_direction(INIT_DIRECTION), m_initPos(position), m_isFalling(false), m_moveElapsed(ELAPSED),
	m_isAscending(false), m_moveStartPos(position), m_moveEndPos(position), m_moveDuration(MOVE_DURATION), m_frameCount(frameCount),
	m_currentFrame(CURRENT_FRAME), m_frameDuration(FRAME_DURATION), m_elapsedTime(ELAPSED) 
{
	m_character.setOrigin(size.x / 2, size.y / 2);
	m_character.setSize(size);	

	setFrames(texture, frameRow, rowsNum, maxPhotos);	
}

void MovingObject::setFrames(const sf::Texture* texture, int frameRow, int rowsNum, int maxPhotos)
{
	// Check if the frame row is valid
	if (maxPhotos == 0 || m_frameCount == 0 || rowsNum == 0)
	{
		throw std::invalid_argument("Invalid frame row or frame count or rows number, trying to divide by zero");
	}

	// Calculate frame width and height
	int frameWidth = ((texture->getSize().x * m_frameCount) / maxPhotos) / m_frameCount;
	int frameHeight = texture->getSize().y / rowsNum;

	// Calculate frame rectangles for the specified row (frameRow)
	for (int x = 0; x < m_frameCount; ++x) {
		sf::IntRect frameRect(x * frameWidth, frameRow * frameHeight, frameWidth, frameHeight);
		m_frames.emplace_back(frameRect);
	}

	m_character.setTextureRect(m_frames[0]);
}

void  MovingObject::updatePhoto(float deltaTime)  //update the photo of the object withing the frame
{
	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_frameDuration)
	{
		m_elapsedTime = ELAPSED;
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		m_character.setTextureRect(m_frames[m_currentFrame]);
	}
}


void MovingObject::setPrevPosition()
{
	m_character.setPosition(m_prevPos);
}

void MovingObject::updateImage(const sf::Vector2f& offset)
{
	if (offset.x < 0) {
		// Moving left
		m_character.setScale(LEFT_SCALE); // Flip horizontally
	}
	else if (offset.x > 0) {
		// Moving right
		m_character.setScale(RIGHT_SCALE); // Normal scale
	}
}

//start the movement of the object - from start position to end position
void MovingObject::startMoving(const sf::Vector2f& startPos, const sf::Vector2f& endPos, float duration, bool ascending)
{
	if (ascending)  //if the object is ascending
	{
		m_isAscending = true;
		m_isFalling = false;
	}
	else  //if the object is falling
	{
		m_isFalling = true;
		m_isAscending = false;
	}

	m_moveStartPos = startPos;
	m_moveEndPos = endPos;
	m_moveDuration = duration;
	m_moveElapsed = ELAPSED;
	setPosition(startPos);
}

//update the movement of the object
void MovingObject::updateMoving(float deltaTime)
{
	m_moveElapsed += deltaTime;
	if (m_moveElapsed >= m_moveDuration)
	{
		m_isFalling = false;
		m_isAscending = false;
	}
	else
	{
		//Calculates how much of the movement has been completed relative to its total duration.
		float t = m_moveElapsed / m_moveDuration;

		//Updates the object's position gradually from the start to the end position based on the interpolation factor t.
		setPosition(m_moveStartPos + t * (m_moveEndPos - m_moveStartPos));
	}
}