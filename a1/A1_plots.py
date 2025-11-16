import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Чтение данных
df = pd.read_csv('experiment_results.csv')

# Точное значение площади
exact_area = 0.25 * np.pi + 1.25 * np.arcsin(0.8) - 1.0

# Настройка стиля графиков
plt.style.use('seaborn-v0_8')
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))

# График 1: Приближенная площадь (широкая область)
ax1.plot(df['N'], df['WideArea'], 'b-', alpha=0.7, label='Монте-Карло')
ax1.axhline(y=exact_area, color='r', linestyle='--', label='Точное значение')
ax1.set_xlabel('Количество точек N')
ax1.set_ylabel('Площадь')
ax1.set_title('Широкая область [0,3]×[0,3]')
ax1.legend()
ax1.grid(True, alpha=0.3)

# График 2: Приближенная площадь (узкая область)
ax2.plot(df['N'], df['NarrowArea'], 'g-', alpha=0.7, label='Монте-Карло')
ax2.axhline(y=exact_area, color='r', linestyle='--', label='Точное значение')
ax2.set_xlabel('Количество точек N')
ax2.set_ylabel('Площадь')
ax2.set_title('Узкая область [1,2]×[1,2]')
ax2.legend()
ax2.grid(True, alpha=0.3)

# График 3: Относительная погрешность (широкая область)
ax3.plot(df['N'], df['WideError'] * 100, 'b-', alpha=0.7)
ax3.set_xlabel('Количество точек N')
ax3.set_ylabel('Относительная погрешность (%)')
ax3.set_title('Погрешность: широкая область')
ax3.grid(True, alpha=0.3)
ax3.set_yscale('log')

# График 4: Относительная погрешность (узкая область)
ax4.plot(df['N'], df['NarrowError'] * 100, 'g-', alpha=0.7)
ax4.set_xlabel('Количество точек N')
ax4.set_ylabel('Относительная погрешность (%)')
ax4.set_title('Погрешность: узкая область')
ax4.grid(True, alpha=0.3)
ax4.set_yscale('log')

plt.tight_layout()
plt.savefig('monte_carlo_results.png', dpi=300, bbox_inches='tight')
plt.show()

# Сравнительный график погрешностей
plt.figure(figsize=(10, 6))
plt.plot(df['N'], df['WideError'] * 100, 'b-', alpha=0.7, label='Широкая область')
plt.plot(df['N'], df['NarrowError'] * 100, 'g-', alpha=0.7, label='Узкая область')
plt.xlabel('Количество точек N')
plt.ylabel('Относительная погрешность (%)')
plt.title('Сравнение погрешностей для разных областей')
plt.legend()
plt.grid(True, alpha=0.3)
plt.yscale('log')
plt.savefig('error_comparison.png', dpi=300, bbox_inches='tight')
plt.show()
