## Why Vulkan AND OpenGL/DirectX/Metal? Why not separate libraries for each?

Since CrossWindow is a cross platform windowing abstraction layer that targets all operating systems, it would be be fair to accompany such a library with a helper library for all graphics APIs, rather than one for DirectX, one for Vulkan, one for OpenGL, etc.

> In the JavaScript world, [Babel](https://babeljs.io/), a library to compile new JavaScript to older JavaScript for compatibility, underwent a major shift in version 6 where the library author split the library up into multiple libraries. This decision was met with a lot of push back but ultimately stuck.

It's hard to set the limits of a library, but if connecting an individual graphics library to CrossWindow becomes too complex, perhaps separating this library to `CrossWindow-Vulkan`, `CrossWindow-DirectX`, etc. would be a good idea, especially if the library grows to support more graphics API versions, rather than the latest version of each library at the time this was written.

If that's the case this library could just compose each of those individual libraries for compatibility/ease of use.