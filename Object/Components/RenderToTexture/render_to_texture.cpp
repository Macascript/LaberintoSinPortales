#include "render_to_texture.h"
#include "../../../Engine/Commons/common_opengl.h"

RenderToTexture::RenderToTexture(Object* obj, int w, int h){
    type = "rendertexture";
    mesh = (Mesh*) obj->getComponent("mesh");

    glGenFramebuffers(1, &glFrameBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, glFrameBufferId);

    // The texture we're going to render to
    unsigned int renderedTexture;
    glGenTextures(1, &renderedTexture);
    mesh->setTexture(new Texture(w,h,renderedTexture));

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, w, h, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout<<"Nos ha jodio"<<std::endl;
}

void RenderToTexture::update(){
    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, glFrameBufferId);
    glViewport(0,0,mesh->texture->w,mesh->texture->h); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}