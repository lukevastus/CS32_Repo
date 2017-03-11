void listAll(const MenuItem* m, string path)
{
    if (m == nullptr)
        return;
    
    if (path != "")
    {
        cout << path << endl;
        path += "/";
    }
    
    if (m->menuItems() != nullptr)
    {
        vector<MenuItem*>::const_iterator it = m->menuItems()->begin();
        while (it != m->menuItems()->end())
        {
            listAll(*it, path + (*it)->name());
            it++;
        }
    }
}