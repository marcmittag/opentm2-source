/*! \file
	Copyright Notice:

	Copyright (C) 1990-2016, International Business Machines
	Corporation and others. All rights reserved
*/

#ifndef _OTMPLUGIN_H_
#define _OTMPLUGIN_H_

/*! \brief Abstract base-class for OpenTM2 plugins */
class __declspec(dllexport) OtmPlugin
{

public:

/*! \enum ePluginType
	Type of the plugin.
*/
	enum ePluginType
	{
		eTranslationMemoryType,	/*!< plugin handles translation-memory objects */
		eDictionaryType,		/*!< plugin handles dictionary objects */
		eMarkupType,			/*!< plugin handles markup objects */
		eDocumentType,			/*!< plugin handles documents */
		eSpellType,				/*!< plugin handles spell checking*/
		eMorphType,				/*!< plugin handles morphologic functionality*/
		eUndefinedType,			/*!< type of plugin is undefined */
		eSharedTranslationMemoryType, 	/*!< plugin handling shared translation-memory objects */
		eToolType, 	        /*!< plugin providing tools */
	};

/*! \enum eUsableState
	Usable-state of the plugin.
*/
	enum eUsableState
	{
		eUsable,	/*!< plugin is usable */
		eNotUsable	/*!< plugin is NOT usable */
	};

/*! \brief Constructor.
	Initializes the type and the "usable"-flag of the plugin-object.
	The derived class has to set this to a valid type and usable-state.
	Otherwise, no processing-method of the object will be called by the PluginManager.
*/
	OtmPlugin()
		:pluginType(eUndefinedType),
		usableState(eNotUsable)
		{};

/*! \brief Destructor. */
	virtual ~OtmPlugin()
		{};

/*! \brief Returns the "usable"-state of the plugin-object.
	The PluginManager queries the state before calling any processing-method.
	If eNotUsable is returned, the processing-method will not be called.
*/
	virtual bool isUsable()
		{return usableState == eUsable;};

/*! \brief Returns the type of the plugin-object. */
	virtual ePluginType getType()
		{return pluginType;};

/*! \brief Returns the name of the plugin.
	The name must be unique among all plugins.
*/
	virtual const char* getName() = 0;

/*! \brief Returns the short description of the plugin. */
	virtual const char* getShortDescription() = 0;

/*! \brief Returns the long description of the plugin. */
	virtual const char* getLongDescription() = 0;

/*! \brief Returns the version of the plugin. */
	virtual const char* getVersion() = 0;

/*! \brief Returns the supplier of the plugin. */
	virtual const char* getSupplier() = 0;

/*! \brief Stops the plugin. 
	Terminating-function for the plugin, will be called directly before
	the DLL containing the plugin will be unloaded.\n
	The method should call PluginManager::deregisterPlugin() to tell the PluginManager
  that the plugin is not active anymore.
  Warning: THIS METHOD SHOULD BE CALLED BY THE PLUGINMANAGER ONLY!
	\param fForce, TRUE = force stop of the plugin even if functions are active, FALSE = only stop plugin when it is inactive
	\returns TRUE when successful

*/
	virtual bool stopPlugin( bool fForce = false ) = 0;

protected:

/*! \brief Type of the plugin-object.
	Has to be set to a different value than eInvalidType when processing-methods
	should be called by the PluginManager.
*/
	ePluginType pluginType;

/*! \brief "Usable"-state of the plugin-object.
	Has to be set to eUsable when processing-methods should be called by the
	PluginManager.
*/
	eUsableState usableState;

/*! \brief Name of the plugin-object.
	Has to be set to a unique name within the DLL.
*/
	char* pluginName;
};


extern "C" {

/*! \relates OtmPlugin
	Initialization-function for the plugin-DLL, will be called directly
	after the DLL has been loaded.\n
	The function should call PluginManager::registerPlugin() for each avaliable
	plugin.
*/
	__declspec(dllexport) unsigned short registerPlugins();   // add return value for P402974
}

/*! Structure for plugin infomation
*/
typedef struct _OTMPLUGININFO
{
  char szName[256];                    // buffer for the plugin name
  char szShortDescription[256];        // buffer for the short description of the plugin
  char szLongDescription[1024];        // buffer for the long description of the plugin
  OtmPlugin::ePluginType eType;    // buffer for the type of the plugin
  char szVersion[256];                 // buffer for the plugin version
  char szSupplier[256];                // buffer for the name of the plugin supplier
  char szDependencies[1024];           // buffer for the list of dependencies (required other plugins and/or other packages)
  int iMinOpenTM2Version;              // minimum OpenTM2 version reqired for this plugin (the number is decimal; e.g. 1.3.1 is stored as 10301, -1 = n/a)
  char szForFutureEnhancements[8096];  // currently unused area for future enhancements
} OTMPLUGININFO, *POTMPLUGININFO;


extern "C" {
/*! \relates OtmPlugin
	Retrieve static information about the plugin contained in this plugin DLL w/o the need to actually create a plugin object
  \param pPluginInfo points to a OTMPLUGINFO structure which receives the plugin information
	\returns 0 if suucessful or an error code
*/
__declspec(dllexport) unsigned short getPluginInfo( POTMPLUGININFO pPluginInfo );


}

#endif // #ifndef _OTMPLUGIN_H_
