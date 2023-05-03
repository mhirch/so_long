int    check_path(char **split, char **m, int x, int y)
{
    t_pos    p;

    p = get_pos(split, 'P');
    if (x == p.x && y == p.y)
        return (1);
    if (split[x][y] == '1')
        return (0);
    if (m[x][y] == '1')
        return (0);
    m[x][y] = '1';
    if (check_path(split, m, x - 1, y))
        return (1);
    if (check_path(split, m, x, y - 1))
        return (1);
    if (check_path(split, m, x + 1, y))
        return (1);
    if (check_path(split, m, x, y + 1))
        return (1);
    m[x][y] = '0';
    return (0);
}