#ifndef B_FONT_H
#define B_FONT_H

#include <memory>
#include <string>
#include <map>
#include "Renderer_GL.h"
#include "Texture.h"

#include "freetype-gl.h"

/** @brief A font that can be used to display text
*	@author Benjamin B�rgisser
*/
class Font
{
public:

	/* Functions */

	/**	@brief Constructor
	*	@param[in] fileName File name including extension
	*	@param[in] fontPixelSize The nominal  font size in pixels (the characters may vary in size)
	*/
	Font(const std::string &fontFileName, GLuint fontPixelSize);

	~Font()	{ reset(); }

	/**	@brief Loads a font file
	*	@param[in] fileName File name including extension
	*/
	void loadFont(const std::string &fontFileName){ init(fontFileName, _fontPixelSize); }

	/**	@brief Set the nominal font size in pixels (the characters may vary in size)
	*	@param[in] fontPixelSize The nominal font size in pixels
	*/
	void setPixelSize(GLuint fontPixelSize) { init(_fontFileName, fontPixelSize); }

	/**	@brief Returns the nominal font size in pixels (the characters may vary in size)
	*/
	GLuint getPixelSize() { return _fontPixelSize; }

	/**	@brief Returns the fil name of the current font (including extension)
	*/
	std::string getFontFileName() { return _fontFileName; }

	/**	@brief Returns a character
	*	@param[in] c The character to get
	*/
	ftgl::texture_glyph_t *getCharacter(char c);

	/**	@brief Returns the character atlas
	*/
	TexturePtr getAtlas(){ return _atlasTexture; }

private:

	/* Functions */

	void init(const std::string &fontFileName, GLuint fontPixelSize);

	void reset();

	/* Variables */

	bool _initialized = false;
	ftgl::texture_atlas_t *_atlas = nullptr;
	ftgl::texture_font_t *_font = nullptr;
	TexturePtr _atlasTexture = nullptr;
	std::string	_fontFileName;
	GLuint _fontPixelSize;
};

typedef std::shared_ptr< Font >  FontPtr;

#endif /* defined(B_FONT_H) */
