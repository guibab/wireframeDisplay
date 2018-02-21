from maya import cmds
cmds.loadPlugin("wireframeDisplay")

""""
prt, construct= cmds.polySphere( radius=1.0, subdivisionsX=20, subdivisionsY=20, axis=[0.0, 1.0, 0.0], createUVs=2, constructionHistory=True)
loc = cmds.createNode ("wireframeDisplay", p=prt)
shp = cmds.listRelatives (prt, s=True)[0]
cmds.connectAttr (shp+".outMesh", loc+".inMesh", f=True)
"""

for mesh in cmds.ls (type = "mesh"):
    prt,=cmds.listRelatives (mesh, p=True, path=True)
    loc = cmds.createNode ("wireframeDisplay", p=prt)
    cmds.setAttr (loc+".inputColor",1,1,0)
    cmds.setAttr (loc+".inputAlpha",0.2)
    cmds.connectAttr (mesh+".outMesh", loc+".inMesh", f=True)
    
    
    
from maya import cmds
cmds.loadPlugin("wireframeDisplay")
for el in cmds.ls (sl=True, tr=True):
    meshes = cmds.listRelatives (el, s=True, type = "mesh")
    meshes  = [shp for shp in meshes if not cmds.getAttr (shp+".intermediateObject")]
    for msh in meshes  :
        loc = cmds.createNode ("wireframeDisplay", p=prt)
        cmds.connectAttr (msh+".outMesh", loc+".inMesh", f=True)    

