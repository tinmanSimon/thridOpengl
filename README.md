# thridOpengl

Made a scene using opengl. Added skybox, one way through glasses, and cube reflection.

I played around with blending effect, and kind of made a one way through glass. The trick is using depth buffer. Basically I just draw the transparent glasses in certain order. For example, let's say I draw the 5 glasses ABCDE from the left to right. Now, if I'm at left of these 5 glasses and looking right, only A will be drawn because A has the lowest depth and A is drawn first. As a result, we can see through A clearly because there are no other glasses drawn behind A. However, if I stand at right of the 5 glasses and looking left, then the 5 glasses will be drawn in the same order from A to E. Then the blending effects of 5 glasses will be added cumulatively, making it blury to see through the glasses. As a result, you can clearly see through these glasses if you stand on left of them, but things will become blury if you stand right of the glasses. Making them one way through glasses.

Credits:
The credits of stb image loading library goes to Sean Barrett.
Glad loader is generated at website https://glad.dav1d.de/, and the credits goes to Dav1dde.
Many thanks to Joey de Vries and his amazing tutorial of opengl. His website is at https://learnopengl.com
