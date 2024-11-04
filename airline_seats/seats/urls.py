from django.urls import path
from . import views

urlpatterns = [
    path('seats/', views.get_seats, name='get_seats'),
    path('seats/add/', views.add_seat, name='add_seat'),
    path('seats/update/', views.update_seat_status, name='update_seat_status'),
]