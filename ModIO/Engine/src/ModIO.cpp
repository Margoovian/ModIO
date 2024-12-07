#include "ModIO.h"

///
/// Audio Session <- Master <- Mixer <- Chain <- Signal <- Generator
///


///
///						- Audio Session -
/// 
/// Is the wrapper around the platform specific low level audio API
/// currently windows WASAPI is the only api that will be supported 
///		but multiple could possibly added down the line.
/// 
/// The audio session can have mixers that will mix audio chains
///		that process signals generated from a generator.
///

///
///							- Master -
/// 
/// Is also a mixer, the master is a special mixer that has the
///	ability to send a buffer of audio to the audio session to be
/// processed, thus it is the last step in the audio chain processing
///					all the data to be sent off.
/// 

/// 
///							- Mixer - 
/// 
/// Is the point where chains converge and are all merged into one
/// source, mixers are meant for mixing so they serve the point to
///		attenuate the volume of the signal, pan, clip, ect
///  

/// 
///							- Chain -
/// Is the point where all effects 
/// 
/// 
/// 