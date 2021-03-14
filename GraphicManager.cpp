#include "GraphicManager.h"

using namespace Manager;

///BODY CLASS METHODS

GraphicManager::Body::Body(const VF size, const string ptexture)
{
    this->setSize(size);
    path = ptexture;
}

GraphicManager::Body::~Body()
{

}

void GraphicManager::Body::setPosition(const VF position)
{
    body.setPosition(sf::Vector2f(position.x, position.y));
}

void GraphicManager::Body::setPosition(const float x, const float y)
{
    body.setPosition(sf::Vector2f(x, y));
}

const VF GraphicManager::Body::getPosition() const
{
    return(Vector2D<float>(body.getPosition().x, body.getPosition().y));
}

void GraphicManager::Body::setSize(const VF size)
{
    body.setSize(sf::Vector2f(size.x, size.y));
    body.setOrigin(sf::Vector2f(size.x/2, size.y/2));
}

void GraphicManager::Body::setSize(const float x, const float y)
{
    body.setSize(sf::Vector2f(x, y));
    body.setOrigin(sf::Vector2f(x/2.0, y/2.0));
}

const VF GraphicManager::Body::getSize() const
{
    return(Vector2D<float>(body.getSize().x, body.getSize().y));
}

void GraphicManager::Body::setTexture(const string ptexture)
{
    path = ptexture;
    if(texture.loadFromFile(path))
    {
        body.setTexture(&texture);
    }
    else
    {
        body.setTexture(nullptr);
    }
}

const string GraphicManager::Body::getTexture() const
{
    return(path);
}

const VF GraphicManager::Body::getTextureSize() const
{
    return(Vector2D<float>(texture.getSize().x, texture.getSize().y));
}

void GraphicManager::Body::putTexture (){
    setTexture(path);
}

void GraphicManager::Body::noTexture()
{
    body.setTexture(nullptr);
}

void GraphicManager::Body::setIntRect(const float width, const float height, const float left, const float top)
{
    uvRect.width = width;
    uvRect.height = height;
    uvRect.left = left;
    uvRect.top = top;
}

void GraphicManager::Body::setTextureRect()
{
    body.setTextureRect(uvRect);
}

void GraphicManager::Body::setColor(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa)
{
    body.setFillColor(sf::Color(red, green, blue, alfa));
}

void GraphicManager::Body::move(const float x, const float y)
{
    body.move(sf::Vector2f(x,y));
}

void GraphicManager::Body::move(const VF moviment)
{
    body.move(sf::Vector2f(moviment.x, moviment.y));
}

sf::RectangleShape* GraphicManager::Body::getBody()
{
    return(&body);
}

const bool GraphicManager::Body::operator == (const Body& c) const
{
    if(getPosition().x == c.getPosition().x)
    {
        if(getPosition().y == c.getPosition().y)
        {
            return(true);
        }
        else
        {
            return(false);
        }
    }
    else
    {
        return(false);
    }
}

const bool GraphicManager::Body::operator == (const Vector2D<float>& p) const
{
    if(this->getPosition().x == p.x)
    {
        if(this->getPosition().y == p.y)
        {
            return(true);
        }
    }
    return(false);
}

const bool GraphicManager::Body::operator != (const Body& c) const
{
    return( !(*this == c) );
}

const bool GraphicManager::Body::operator != (const Vector2D<float>& p) const
{
    return( !(*this == p) );
}

///MÉTODOS DA CLASS TEXT

GraphicManager::Text::Text(){}
GraphicManager::Text::~Text(){}

const bool GraphicManager::Text::setFont(const string f)
{
    if(!font.loadFromFile(f))
    {
        return false; // hadle error
    }

    text.setFont(font);
    return(true);
}

void GraphicManager::Text::setFillColor(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa)
{
    text.setFillColor(sf::Color(red,blue,green,alfa));
}
void GraphicManager::Text::setString(const string s)
{
    text.setString(s);
}
void GraphicManager::Text::setPosition(const VF position)
{
    text.setPosition(sf::Vector2f(position.x, position.y));
}

void GraphicManager::Text::setCharacterSize(size_t size)
{
    text.setCharacterSize(size);
}

sf::Text* GraphicManager::Text::getText()
{
    return(&text);
}

///GRAPHIC MANAGER CLASS METHODS

float GraphicManager::delta_time = 0.0f;

GraphicManager::GraphicManager(const string name, const Vector2D<unsigned int> window_size):
    window(sf::VideoMode(window_size.x, window_size.y), name, sf::Style::Close | sf::Style::Resize),
    view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(window_size.x), static_cast<float>(window_size.y)))

{
    swy = (float)window_size.y;
    text.setFont("Font/ARDESTINE.ttf");
}

GraphicManager::~GraphicManager()
{
    while(!manager.empty())
    {
        map<string, Body*>::iterator it = manager.begin();
        delete(it->second);
        manager.erase(it);
    }
    cout << "\nConcluido!!!\n";
}

bool GraphicManager::isOpen()
{
    return(window.isOpen());
}

bool GraphicManager::pollEvent()
{
    return(window.pollEvent(evento));
}

void GraphicManager::clear()
{
    window.clear();
}

void GraphicManager::clear(const unsigned char red ,const unsigned char green, const unsigned char blue)
{
    window.clear(sf::Color(red, green, blue));
}

void GraphicManager::display()
{
    window.display();
}

void GraphicManager::close()
{
    window.close();
}

const bool GraphicManager::closed()
{
    return(evento.type == sf::Event::Closed);
}

void GraphicManager::ResizeView()
{
    float razao = (float)window.getSize().x / window.getSize().y;
    view.setSize(view.getSize().y * razao, view.getSize().y);
}

bool GraphicManager::Resized()
{
    return(evento.type == sf::Event::Resized);
}

void GraphicManager::setTitle(const string window_name)
{
    window.setTitle(window_name);
}

void GraphicManager::setVerticalSyncEnabled(const bool key)
{
    window.setVerticalSyncEnabled(key);
}

void GraphicManager::setFramerateLimit(const unsigned long int vel)
{
    window.setFramerateLimit(vel);
}

void GraphicManager::setFramerateLimitTime(const float time)
{
    float t = 1 / time;
    window.setFramerateLimit(t);
}

const VF GraphicManager::getPositionWindow() const
{
    return(Vector2D<float>(window.getPosition().x, window.getPosition().y));
}

float GraphicManager::WindowRation()
{
    return(window.getSize().y / swy);
}

const VF GraphicManager::getSizeWindow() const
{
    return( Vector2D<float>(window.getSize().x, window.getSize().y) );
}

const VF GraphicManager::getSizeView() const
{
    return( VF(view.getSize().x, view.getSize().y) );
}

void GraphicManager::setView()
{
    window.setView(view);
}

void GraphicManager::setPositionView(VF position)
{
    view.setCenter(sf::Vector2f(position.x, position.y));
}

VF GraphicManager::getPositionView() const
{
    return( VF ( view.getCenter().x, view.getCenter().y) );
}

void GraphicManager::Centralize(const float x1, const float y1, const float x2, const float y2)
{
    view.setCenter( sf::Vector2f( (x2 + x2) / 2.0, (y1 + y2 - 200.0f) / 2.0) );
}

void GraphicManager::Centralize(const VF v1, const VF v2)
{
    view.setCenter(sf::Vector2f( (v1.x + v2.x)/ 2.0, (v1.y + v2.y - 200.0f) / 2.0 ) );
}

void GraphicManager::Centralize(const float x, const float y)
{
    VF cam = getPositionView();
    if(x < cam.x - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER || x > cam.x + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
    {
        if(x > cam.x + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
        {
            cam.x = x - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
        else
        {
            cam.x = x + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
    }
    if(y < cam.y - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER || y > cam.y + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
    {
        if(y > cam.y + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
        {
            cam.y = y - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
        else
        {
            cam.y = y + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
    }
    view.setCenter(sf::Vector2f(cam.x, cam.y));
}

void GraphicManager::Centralize(const VF v) //using
{
    VF cam = getPositionView();
    if(v.x < cam.x - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER || v.x > cam.x + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
    {
        if(v.x > cam.x + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
        {
            cam.x = v.x - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
        else
        {
            cam.x = v.x + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
    }
    if(v.y < cam.y - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER || v.y > cam.y + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
    {
        if(v.y > cam.y + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER)
        {
            cam.y = v.y - MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
        else
        {
            cam.y = v.y + MAXIMUM_DISTANCE_FROM_CAMERA_TO_PLAYER;
        }
    }
    view.setCenter(sf::Vector2f(cam.x, cam.y));
}

void GraphicManager::DrawLife01()
{
    ptrR = HealthBar01.getBody();
    window.draw(*ptrR);
}

const bool GraphicManager::isPW() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
}

const bool GraphicManager::isPS() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
}

const bool GraphicManager::isPA() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
}

const bool GraphicManager::isPD() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
}

const bool GraphicManager::isPR() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::R));
}

const bool GraphicManager::isPP() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::P));
}

const bool GraphicManager::isPEnter() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
}

const bool GraphicManager::isP_UP() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
}

const bool GraphicManager::isP_Down() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
}

const bool GraphicManager::isP_Left() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
}

const bool GraphicManager::isP_Right() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
}

const bool GraphicManager::isP_ALT() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt));
}

const bool GraphicManager::isP_Space() const
{
    return(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}

const bool GraphicManager::isM_Left() const
{
    return(sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

const bool GraphicManager::isM_Right() const
{
    return(sf::Mouse::isButtonPressed(sf::Mouse::Right));
}

const VF GraphicManager::getPositionMouse() const
{
    return(Vector2D<float>(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
}

void GraphicManager::set_Delta_Time()
{
    delta_time = clock.restart().asSeconds();
    if(delta_time >= 0.05f)
    {
        delta_time = 0.05f;
    }
}

float GraphicManager::get_Delta_Time()
{
    return(delta_time);
}

void GraphicManager::removeTexture()
{
    map<string, Body*>::iterator it;
    for(it = manager.begin(); it != manager.end(); ++it)
    {
        it->second->noTexture();
    }
    HealthBar01.noTexture();
}

void GraphicManager::putTexture()
{
    map<string, Body*>::iterator it;
    for(it = manager.begin(); it != manager.end(); ++it){
        it->second->putTexture();
    }
}

///LIFE BAR CLASS METHODS

void GraphicManager::setPositionLife01()
{
    sf::Vector2f center = view.getCenter();
    sf::Vector2i tamanho;
    tamanho.x = view.getSize().x / 2;
    tamanho.y = view.getSize().y / 2;
    center.x -= tamanho.x;
    center.y -= tamanho.y;
    center.x = center.x + (HealthBar01.getSize().x / 2);
    center.y = center.y + (HealthBar01.getSize().y / 2);

    HealthBar01.setPosition(center.x, center.y);
}

void GraphicManager::setSizeLife01(const VF v)
{
    HealthBar01.setSize(v);
}

void GraphicManager::setSizeLife01(const float x, const float y)
{
    HealthBar01.setSize(x,y);
}

void GraphicManager::setTextureLife01(const string t)
{
    HealthBar01.setTexture(t);
}

VF GraphicManager::getTextureSizeLife01() const
{
    return( HealthBar01.getTextureSize() );
}

void GraphicManager::setIntRectLife01(const float width, const float height, const float left, const float top)
{
    HealthBar01.setIntRect(width, height, left, top);
}

void GraphicManager::setTextureRectLife01()
{
    HealthBar01.setTextureRect();
}

void GraphicManager::moveLife01(const VF v)
{
    HealthBar01.move(v);
}

void GraphicManager::moveLife01(const float x, const float y)
{
    HealthBar01.move(x,y);
}

///METODOS DEDICADOS PARA BARRA DE VIDA 02

void GraphicManager::setPositionLife02()
{
    sf::Vector2f center = view.getCenter();
    sf::Vector2i viewsize;
    viewsize.x = view.getSize().x / 2;
    viewsize.y = view.getSize().y / 2;
    center.x -= viewsize.x;
    center.y -= viewsize.y;
    center.x = center.x + (HealthBar02.getSize().x / 2);
    center.y = center.y + HealthBar02.getSize().y;

    HealthBar02.setPosition(center.x, center.y);
}

void GraphicManager::setSizeLife02(const VF v)
{
    HealthBar02.setSize(v);
}

void GraphicManager::setSizeLife02(const float x, const float y)
{
    HealthBar02.setSize(x,y);
}

void GraphicManager::setTextureLife02(const string t)
{
    HealthBar02.setTexture(t);
}

VF GraphicManager::getTextureSizeLife02() const
{
    return( HealthBar02.getTextureSize() );
}

void GraphicManager::setIntRectLife02(const float width, const float height, const float left, const float top)
{
    HealthBar02.setIntRect(width, height, left, top);
}

void GraphicManager::setTextureRectLife02()
{
    HealthBar02.setTextureRect();
}

void GraphicManager::moveLife02(const VF v)
{
    HealthBar02.move(v);
}

void GraphicManager::moveLife02(const float x, const float y)
{
    HealthBar02.move(x,y);
}

///MAP

GraphicManager::Body* GraphicManager::getMap(const string key)
{
    map<string, Body*>::iterator it;
    it = manager.find(key);
    if(it == manager.end())
    {
        return(NULL);//NÃO ACHOU A INFORMAÇÃO COM ESSA CHAVE
    }

    return(it->second);
}

const bool GraphicManager::ThereIsThisKey(const string key)
{
    map<string, Body*>::iterator it;
    it = manager.find(key);

    if(it == manager.end())
    {
        //Não encontro a chave
        return(false);
    }

    return(true);
}

void GraphicManager::AdicionarBotaoNoMenu(const string key, const string texture, const VF position, const VF sizeB)
{
    if(!ThereIsThisKey(key))
    {
        Body* aux = new Body();
        aux->setSize(sizeB);
        aux->setPosition(position);
        aux->setTexture(texture);
        manager.insert(pair<string, Body*>(key, aux));
    }
    else
    {
        cout << "Error: Chave não Valida, portanto não criado o Botão" << endl;
    }
}

void GraphicManager::ajustarBotoes(const string key, const unsigned long int number_of_button, const unsigned long int indice)
{
    if(ThereIsThisKey(key))
    {
        Body* aux = getMap(key);
        VF window_size;
        VF window_position;

        window_size.x = view.getSize().x / number_of_button;
        window_size.y = view.getSize().y / number_of_button;
        window_position.x = view.getCenter().x;
        window_position.y = view.getCenter().y - (view.getSize().y/2) + aux->getSize().y/2;
        window_position.y += indice * aux->getSize().y;

        aux->setPosition(window_position);
    }
}

VF GraphicManager::getPositionButton(const string key)
{
    if(ThereIsThisKey(key))
    {
        Body* aux = getMap(key);
        return(aux->getPosition());
    }

    cout << "Botao " << key << "Não Existe - retorno na Posicao Padrao" << endl;
    return(Vector2D<float>(-1000.0f, -1000.0f));

}

VF GraphicManager::getSizeButton(const string key)
{
    if(ThereIsThisKey(key))
    {
        Body* aux = getMap(key);
        return(aux->getSize());
    }

    cout << "Botao " << key << "Não Existe - retorno na Tamanho Padrao" << endl;
    return(Vector2D<float>(100.0f, 100.0f));
}

void GraphicManager::DrawMap(const string key)
{
    if(ThereIsThisKey(key))
    {
        ptrR = getMap(key)->getBody();
        window.draw(*ptrR);
    }
    else
    {
        cout << "Manager Error: DrawMap command - Key: " << key << endl;
    }
}

void GraphicManager::DrawMapBotao(const string key, const bool active)
{
    if(ThereIsThisKey(key))
    {
        Body* aux = getMap(key);
        VF left_top;
        VF width_height;
        width_height = aux->getTextureSize();
        width_height.x /= 2.0;
        left_top.y = 0.0f;
        if(active)
        {
            left_top.x = width_height.x;
            //left_top.x = 0.0f;
        }
        else
        {
            left_top.x = 0.0f;
            //left_top.x = width_height.x;
        }

        aux->setIntRect( width_height.x, width_height.y, left_top.x, left_top.y);
        aux->setTextureRect();
        window.draw(*(aux->getBody()));
    }
    else
    {
        cout << "Error Manager: Comando DrawMap - Chave: " << key << endl;
    }
}

///MENU METHODS

GraphicManager::Body* GraphicManager::getSecond(const string key)
{
    map<string, Body*>::iterator it;
    it = manager.find(key);

    if(it == manager.end())
    {
        return(NULL);
    }

    return(it->second);
}

void GraphicManager::addBody(const string key)
{
    map<string, Body*>::iterator it;
    it = manager.find(key);
    if(it == manager.end())
    {
        Body* aux = new Body();
        manager.insert(pair<string, Body*>(key, aux));
    }
    else
    {
        cout << "ERRO: CORPO DA CHAVE " << key << " não adicionado!!!" << endl;
    }
}

void GraphicManager::setPosition(const string key, const VF position)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setPosition(position);
    }
    else
    {
        cout<< "ERRO: em seta posicao da chave: " << key << endl;
    }
}

void GraphicManager::setPosition(const string key, const float x, const float y)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setPosition(x,y);
    }
    else
    {
        cout <<"Erro em seta a chave "<< key << "\n\n";
    }
}

const VF GraphicManager::getPosition(const string key)
{
    if(ThereIsThisKey(key))
    {
        return(getSecond(key)->getPosition());
    }
    else
    {
        cout << "ERRO: GET POSITION " << key << " não adicionado!!!" << endl;
        return(VF(0.0f,0.0f));
    }

}

void GraphicManager::setSize(const string key, const VF tam)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setSize(tam);
    }
    else
    {
        cout << "Erro em seta tamanho da chave " << key << endl;
    }
}

void GraphicManager::setSize(const string key, const float x, const float y)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setSize(x,y);
    }
    else
    {
        cout << "Erro em seta tamanho da chave " << key << endl;
    }
}

const VF GraphicManager::getSize(const string key)
{
    if(ThereIsThisKey(key))
    {
        return(getSecond(key)->getSize());
    }
    else
    {
        cout << "Erro retorna tamanho da chave " << key << endl;
        return(VF(100.0f, 100.0f));
    }

}

void GraphicManager::setTexture(const string key, const string texture)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setTexture(texture);
    }
    else
    {

    }
}

const string GraphicManager::getTexture(const string key)
{
    if(ThereIsThisKey(key))
    {
        return(getSecond(key)->getTexture());
    }
    else
    {
        cout << "Error: Key does not exist - getTexture" << endl;
        return("Texture/menuPause.png");
    }
}

void GraphicManager::removeTexture(const string key)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->noTexture();
    }
    else
    {
        cout << "Error: Key does not exist - removeTexture" << endl;
    }
}

const VF GraphicManager::getTextureSize(const string key)
{
    if(ThereIsThisKey(key))
    {
        return(getSecond(key)->getTextureSize());
    }
    else
    {
        cout << "ERRO GET TEXTURE SIZE " << endl;
        return(VF(100.0f, 100.0f));
    }
}

void GraphicManager::setIntRect(const string key, const float width, const float height, const float left, const float top)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setIntRect(width, height, left, top);
    }
    else
    {
        cout << "Erro in set int rect " << key <<endl;
    }
}
void GraphicManager::setTextureRect(const string key)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setTextureRect();
    }
}

void GraphicManager::Move(const string key, const VF movement)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->move(movement);
    }
}
void GraphicManager::Move(const string key, const float x, const float y)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->move(x,y);
    }
}

void GraphicManager::Draw(const string key)
{
    if(ThereIsThisKey(key))
    {
        window.draw(*(getSecond(key)->getBody()));
    }
    else
    {
        cout << "Erro: \n" << key << endl;
    }
}

void GraphicManager::setColor(const string key, const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa)
{
    if(ThereIsThisKey(key))
    {
        getSecond(key)->setColor(red, green, blue, alfa);
    }
}

const bool GraphicManager::setFontText(const string f)
{
    return(text.setFont(f));
}

void GraphicManager::setFillColorText(const unsigned char red, const unsigned char green, const unsigned char blue, const unsigned char alfa)
{
        text.setFillColor(red, green, blue, alfa);
}
void GraphicManager::setStringText(const string s)
{
    text.setString(s);
}
void GraphicManager::setPositionText(const VF position)
{
    text.setPosition(position);
}
void GraphicManager::setPositionText(const float x, const float y)
{
    text.setPosition(VF(x,y));
}
void GraphicManager::setCharacterSizeText(size_t size_)
{
    text.setCharacterSize(size_);
}

void GraphicManager::DrawTextMY()
{
    window.draw(*text.getText());
}

void GraphicManager::DrawTextMY(const string t)
{
    text.setString(t);
    window.draw(*text.getText());
}

