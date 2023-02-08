from setuptools import find_packages
from setuptools import setup

setup(
    name='knapp_amr',
    version='1.0.0',
    packages=find_packages(
        include=('knapp_amr', 'knapp_amr.*')),
)
