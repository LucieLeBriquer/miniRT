#include "miniRT.h"
#include <stdio.h>

void	ft_addobj(t_obj **obj, t_obj *obj_new)
{
	obj_new->next = *obj;
	*obj = obj_new;
}

void	ft_objiter(t_obj *objs, void (*f)(t_obj))
{
	while (objs)
	{
		(*f)(*objs);
		objs = objs->next;
	}
}

t_obj	*new_obj(int type, t_vect o, t_vect axe, t_col col, float r, float h)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = type;
	obj->o = o;
	obj->axe = axe;
	normalize(&(obj->axe));
	obj->col = col;
	obj->r = r;
	obj->h = h;
	obj->next = NULL;
	return (obj);
}

void	show_obj(t_obj obj)
{
	printf("Obj :\ttype(%d)", obj.type);
	printf("\n\torigin(%f,%f,%f)", obj.o.x, obj.o.y, obj.o.z);
	printf("\n\tcolor(%d,%d,%d)", obj.col.r, obj.col.g, obj.col.b);
	printf("\n\tr = %f\th=%f\n\n", obj.r, obj.h);
}
