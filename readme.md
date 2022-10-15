# Materiel

## Goal
What I hope to do with this project is learn how to create textures from scratch using the GPU.
There is a few very well-made procedural material generator out there which I can't hope to compete with such as
Substance or the very well done Material Maker. However, after using MM for a little while I've come to regret the
direction its development went. It did spring some idea about what approach I would take for such a software.
By combining Blender's approach to Geometry Nodes and the simple concepts behind MM I think I could create a satisfying
material making experience.
### Main features and objectives
* On demand processing. Only render frame when needed and cache the results for later use
* context evaluation. Similar to Blender's Geometry node where you can pass a single value or an array of values per
elements you would pass either a set of value for the whole texture or, using contexts, multiple values. Context are
subsection of the texture, such as individual bricks in a brick generator, context enable you to reevaluate each node
that supports it for has many context there are. This should make creating variation very easy
* material datatype. Linking special nodes with a Material Link datatype will connect inputs with any output of the same
id, all under a single link. This enables you to manage material at a higher level or work on all the texture at the same
time. Ex: Mixing material, creating a tileable material, etc.