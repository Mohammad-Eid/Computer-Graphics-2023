1- Orthogtaphic projection:
here are results showing the change that happens when we change the view volume via (up,down,right,left) to the same model withe same scale
(1)
-> ![Screen Shot 2022-12-23 at 14 39 43](https://user-images.githubusercontent.com/80767830/209340936-7c471433-01fb-46f9-a14f-7e8e48d713c1.png)
(2)
-> ![Screen Shot 2022-12-23 at 14 39 11](https://user-images.githubusercontent.com/80767830/209341090-34856b2e-4933-47c6-8a59-dc1d889293d3.png)


2- Camera repositioning :
all the controls of the camera are through the GUI where we allow the user to control the position of the camera among other controls, the position 
controls are either the translation matrices or the position victor off the camera that goes into the LookAt matrex (transformation).
we allow the user to control each value of the position seperately (X,Y,Z) and after each change we update all the relevant transforms


3- View volume:
demonstration of changing the size of the window, in the demonstration we can see that the model size doesn't change while maintaining the same scale and transformation but the window size changes.
(1)
-><img width="1792" alt="Screen Shot 2022-12-24 at 0 03 57" src="https://user-images.githubusercontent.com/80767830/209409278-f3c4b226-1a7e-476c-989e-e651d80d1d37.png">
(2)
-><img width="1792" alt="Screen Shot 2022-12-24 at 0 03 29" src="https://user-images.githubusercontent.com/80767830/209409295-aa65c7f2-48bc-4b4c-82d0-7fb385e80677.png">
(3)
-><img width="1792" alt="Screen Shot 2022-12-24 at 0 03 44" src="https://user-images.githubusercontent.com/80767830/209409304-b22a1c09-f713-40a2-b8ac-efc5da246f3f.png">


4-Model axis in loccal and world frams:
(one coordenate system (Local) is the colors light blue,yellow,pink
and the other (World) is red,green,blue)
first two pictures shoe the axis with local transformations on the model:
<img width="1392" alt="Screen Shot 2022-12-24 at 0 13 16" src="https://user-images.githubusercontent.com/80767830/209409844-37277e3e-b193-4bba-8b55-4a0093696da3.png">
<img width="1392" alt="Screen Shot 2022-12-24 at 0 13 39" src="https://user-images.githubusercontent.com/80767830/209409848-a8a8163d-d87c-4526-a52b-d5bb16869ed9.png">
then two photos showing world transformations on the model:
<img width="1392" alt="Screen Shot 2022-12-24 at 0 13 52" src="https://user-images.githubusercontent.com/80767830/209409870-36be0de8-2265-4797-8430-c258165884cc.png">
<img width="1392" alt="Screen Shot 2022-12-24 at 0 14 09" src="https://user-images.githubusercontent.com/80767830/209409877-bb437df3-0035-405f-a53e-880b889e8cd8.png">
and the last picture shows both local axis and world axis at the same in the model, showing they get affected by the same transformations:
<img width="1392" alt="Screen Shot 2022-12-24 at 0 14 43" src="https://user-images.githubusercontent.com/80767830/209409921-7b1e0cfd-9479-4108-b07a-956465b13648.png">



5- In this demonstration the bunny has a translation transformation througth the local frame and rotation through the world frame, and for the cow model the opposite translation through world frame and rotation through local frame:
two pictures to show the controls for each model (where it says model name):
<img width="1904" alt="Screen Shot 2022-12-24 at 13 42 49" src="https://user-images.githubusercontent.com/80767830/209434437-e87a43f6-e5db-437b-95f5-3cf4156a41e3.png">
<img width="1904" alt="Screen Shot 2022-12-24 at 13 43 19" src="https://user-images.githubusercontent.com/80767830/209434440-3755c925-03b2-4b2e-8916-9ab346ea20d0.png">






6- Bounding box Local and World:
in pink we have the local bounding box and in blue the world bounding box
<img width="1392" alt="Screen Shot 2022-12-24 at 0 20 38" src="https://user-images.githubusercontent.com/80767830/209410180-45d77d5b-8928-4390-bf93-4dba52257fcb.png">

<img width="1392" alt="Screen Shot 2022-12-24 at 0 20 46" src="https://user-images.githubusercontent.com/80767830/209410197-45249105-17ef-4995-9e6c-0a68fc083edf.png">

<img width="1392" alt="Screen Shot 2022-12-24 at 0 20 55" src="https://user-images.githubusercontent.com/80767830/209410205-ada2d356-352f-438d-901e-28847030ff71.png">

<img width="1392" alt="Screen Shot 2022-12-24 at 0 21 02" src="https://user-images.githubusercontent.com/80767830/209410210-cba41d1d-b4f9-472d-b11b-1dfb5486010a.png">

<img width="1392" alt="Screen Shot 2022-12-24 at 0 21 09" src="https://user-images.githubusercontent.com/80767830/209410216-630921ca-59c1-460d-a846-f43e3c5ab9f2.png">
 
 
 7- Face normals and Vertex Normals:
 <img width="1392" alt="Screen Shot 2022-12-24 at 0 33 27" src="https://user-images.githubusercontent.com/80767830/209410783-d05988ec-2106-462b-a581-a21aaff15eed.png">
<img width="1392" alt="Screen Shot 2022-12-24 at 0 33 36" src="https://user-images.githubusercontent.com/80767830/209410790-f8dd2583-8e39-419a-9f7b-bbfefabcb6ca.png">
<img width="1392" alt="Screen Shot 2022-12-24 at 0 33 43" src="https://user-images.githubusercontent.com/80767830/209410798-3e1afab0-dbae-4fcf-a38c-30bed0bb6d11.png">

8- Misiing

9- ![WhatsApp Image 2022-12-24 at 3 49 12 PM (2)](https://user-images.githubusercontent.com/80767830/209468145-5d5f5dfe-b46d-4373-af5c-801c38aae5f9.jpeg)
![WhatsApp Image 2022-12-24 at 3 49 12 PM (1)](https://user-images.githubusercontent.com/80767830/209468147-5fdd54af-d689-4ef4-bc8c-3ba5f5f7b5ad.jpeg)
![WhatsApp Image 2022-12-24 at 3 49 12 PM](https://user-images.githubusercontent.com/80767830/209468148-c4358ae7-9386-441b-a5f8-5d1c7c74a9c9.jpeg)



10- camera position: 
showing screenshots with two camera positions with different orientations
(a,a,a)=(8,8,8)
<img width="1904" alt="Screen Shot 2022-12-24 at 1 27 51" src="https://user-images.githubusercontent.com/80767830/209413330-0c6ca2b5-d804-4753-80a1-abb8066db30f.png">
<img width="1904" alt="Screen Shot 2022-12-24 at 1 28 23" src="https://user-images.githubusercontent.com/80767830/209413345-81739774-b0b6-4e5e-bb3b-f6a4d9a82cd8.png">
(a,a,a)=(-2,-2,-2)
 <img width="1904" alt="Screen Shot 2022-12-24 at 1 29 02" src="https://user-images.githubusercontent.com/80767830/209413365-33a93f70-c662-43c2-9d8f-d0ecb6e2d4ed.png">

11- Misiing


12- In the following screen shots we have two models and two cameras, all the controls for the models and the cameras are visible.
we can see the active camera index and active model index so we distinguish between different cameras.
<img width="1904" alt="Screen Shot 2022-12-24 at 13 49 00" src="https://user-images.githubusercontent.com/80767830/209434869-eb8db2ca-c3d6-4e98-ada8-5bf589c255f7.png">
<img width="1904" alt="Screen Shot 2022-12-24 at 13 49 12" src="https://user-images.githubusercontent.com/80767830/209434906-5871dae9-9f47-43b8-b1e7-66cac203d29d.png">
<img width="1904" alt="Screen Shot 2022-12-24 at 13 49 57" src="https://user-images.githubusercontent.com/80767830/209434892-fed2fc83-c090-4e08-bd95-4bdeb96811b8.png">
<img width="1904" alt="Screen Shot 2022-12-24 at 13 50 14" src="https://user-images.githubusercontent.com/80767830/209434909-0e9b0ba0-358c-4186-8ca4-a01aa8f378fd.png">
<img width="1904" alt="Screen Shot 2022-12-24 at 13 50 19" src="https://user-images.githubusercontent.com/80767830/209434918-2ec5cd3b-4b7c-4100-998d-3f693fe1ee17.png">


13- Most of the GUI we built to help test the features implemented:
<img width="1904" alt="Screen Shot 2022-12-24 at 1 30 39" src="https://user-images.githubusercontent.com/80767830/209413399-888c0bcf-c1a7-482c-93e2-02abb92a8756.png">
