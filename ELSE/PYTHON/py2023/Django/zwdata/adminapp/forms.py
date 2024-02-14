from django import forms
from userapp.models import *


class DateTimeInput(forms.DateTimeInput):
    input_type = 'datetime-local'


class AffairForm(forms.ModelForm):
    class Meta:
        model = Affair
        exclude = []
        widgets = {
            'Time': DateTimeInput,
            'RepTime': DateTimeInput,
        }

    def __init__(self, *args, **kwargs):
        super(AffairForm, self).__init__(*args, **kwargs)

        for fieldname in self.base_fields:  # 循环给所有字段加样式
            field = self.base_fields[fieldname]
            field.widget.attrs.update({'class': 'form-control'})
