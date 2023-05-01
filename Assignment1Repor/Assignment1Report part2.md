in this part of the assignment we load a mesh into the program, first we display the contents of the .obj file
by printing them onto the command line.

then we scaled up the model using a scaling matrix as we learned in the lectures, since we a vector that contains 3 points
we had to normalize it (convert to vec4) first to be able to multiply it by the scaling matrix.

after scaling the coordenates we started implementing the transformation matrices that we learned about, such as 
translation matrix and rotation matrices.

in addition we designed a GUI that would help us test and demonstrate the functionality we added.


1. a screen shot of the output that we printed to the cmd (not all the the vertices and faces are shown in the screenshot)
![image_2022-11-26_00-52-41](https://user-images.githubusercontent.com/80767830/204611427-08f0c825-0a7c-4b95-92b6-752efbb918aa.png)


2. as said in the introduction the scaling was done by using a scaling matrix and multiplying it with the vector which has been normalized/



3.Screenshot displaying the model in the middle of the screen
<img width="1392" alt="loaded_model" src="https://user-images.githubusercontent.com/80767830/204611825-711558d5-09ca-4d7c-bb2e-5679675f6468.png">



4.The final transformation is done in the following order: first we translate the object using the translation matrices
then we perform the rotation usin the x,y and z rotation matrices, and lastly we perform the scaling.

since we have two translations and two rotations, world and local. we first perform the world transformations and
then we perform the local transformations and lastly scaling.

Screenshot of the GUI built with the help of the given example in the code:
<img width="484" alt="GUI" src="https://user-images.githubusercontent.com/80767830/204612524-b4e17017-8ff8-4c23-a78d-a08f4f0ed746.png">




5.demonstaration of the transformations:
First we have Local translation with World rotation:
<img width="1744" alt="W_rotation_L_translation_1" src="https://user-images.githubusercontent.com/80767830/204615579-0a921ab2-c0b9-4516-b545-ce40587675b9.png">
<img width="1744" alt="W_rotation_L_translation_2" src="https://user-images.githubusercontent.com/80767830/204615598-c9b84865-5e5b-4915-8903-e3c7ad91b834.png">

Then we have Local rotation with World translation:
<img width="1744" alt="W_translation_L_rotation" src="https://user-images.githubusercontent.com/80767830/204615717-9a75cc95-21c2-4804-a4d2-a55529730c47.png">



6.demonstration of two moedls loaded and controlled separately:

<img width="1629" alt="Screen Shot 2022-11-29 at 19 58 01" src="https://user-images.githubusercontent.com/80767830/204615879-1491709c-7ede-49f8-a502-e9d6bdc3b951.png">
<img width="1629" alt="Screen Shot 2022-11-29 at 19 57 10" src="https://user-images.githubusercontent.com/80767830/204615881-dd299610-ef8a-41f6-92e2-224bc7d347e5.png">
<img width="1629" alt="Screen Shot 2022-11-29 at 19 56 17" src="https://user-images.githubusercontent.com/80767830/204615886-e821d090-f815-4e5f-b469-39776bb3a471.png">



7. finlly to control the model using the keyboard we added functions to use the W,A,S,D keys to control the
local translation of which ever model is the active one (we can control which model is the active moel using the 
GUI that we created)
we implemented that in The "io.WantCaptureKeyboard" window in main.cpp following an examples that was there.

